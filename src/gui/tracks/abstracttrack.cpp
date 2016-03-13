#include "abstracttrack.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QApplication>
#include <QGraphicsScene>
#include <QVariantMap>
#include <QStyleOptionProgressBar>
#include <QStyleOptionFrame>
#include <QStyleOptionRubberBand>
#include "app.h"
#include "tracklistwidget.h"
namespace big {
namespace gui {

AbstractTrack::AbstractTrack(QGraphicsItem *parent)
    :QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsSelectable);

    mAnimation = new QPropertyAnimation(this,"y");
    setHeight(200);
}

QRectF AbstractTrack::boundingRect() const
{
    int w = scene()->views().first()->width();
    return QRect(0,0,w,height());

}

int AbstractTrack::height() const
{
    return mHeight;
}

void AbstractTrack::setHeight(int h)
{
    mHeight = h;
}

void AbstractTrack::setSlot(int slot)
{
    mSlot = slot;
    update();
}

int AbstractTrack::slot() const
{
    return mSlot;
}

void AbstractTrack::updatePositionFromSlot()
{
    if (mAnimation->state() == QAbstractAnimation::Running)
        mAnimation->stop();


    mAnimation->setStartValue(pos().y());
    mAnimation->setEndValue(trackList()->rowToPixel(slot()));
    mAnimation->setDuration(200);
    mAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    mAnimation->start();


}

void AbstractTrack::setTrackList(TrackListWidget *parent)
{
    mTrackList = parent;
}

void AbstractTrack::paintRegion(const QString &chromosom, quint64 start, quint64 end)
{

}


//void AbstractTrack::updatePositionFromRow()
//{

////    mAnimation->setStartValue(pos().y());
////    mAnimation->setEndValue(trackList()->rowToPixel(mRow));
////    mAnimation->setDuration(500);
////    mAnimation->setEasingCurve(QEasingCurve::InOutCubic);
////    mAnimation->start();

//}

void AbstractTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::transparent);
    painter->setRenderHint(QPainter::Antialiasing);
    if (isSelected()){
        QColor col  =qApp->style()->standardPalette().color(QPalette::Highlight);
        col.setAlpha(50);
        QBrush brush(col);
        painter->setBrush(brush);

    }

    else
        painter->setBrush(qApp->style()->standardPalette().color(QPalette::Base));

    painter->drawRect(boundingRect());

    // Draw toolbar
    QRect toolbarRect =  boundingRect().toRect();
    toolbarRect.setWidth(40);

    QStyleOption op;
    op.rect = toolbarRect;

    painter->setBrush(qApp->style()->standardPalette().color(QPalette::Window));
    qApp->style()->drawPrimitive(QStyle::PE_Frame, &op,painter);

    op.rect = toolbarRect;

    qApp->style()->drawControl(QStyle::CE_Splitter, &op,painter);




    QVariantMap options;
    options.insert( "color" , qApp->style()->standardPalette().color(QPalette::WindowText));
    QPoint iconPos = toolbarRect.topLeft();
    iconPos += QPoint(10,10);
    painter->drawPixmap(iconPos, App::awesome()->icon(fa::cogs, options).pixmap(20,20));




    // draw rubber
//    QStyleOptionRubberBand bandOption;
//    bandOption.shape = QRubberBand::Rectangle;
//    bandOption.rect.setWidth(boundingRect().toRect().width()-100);
//    bandOption.rect.setHeight(10);


//    qApp->style()->drawControl(QStyle::CE_RubberBand, &bandOption, painter);






    //    QStyleOptionFrame frameOption;
    //    frameOption.features = QStyleOptionFrame::Rounded;
    //    frameOption.rect = boundingRect().toRect();

    //    qApp->style()->drawPrimitive(QStyle::PE_Frame,&frameOption, painter );



    painter->drawText(boundingRect(),Qt::AlignCenter,  QString("%1 0x%2").arg(slot()).arg((quintptr)this,
                                                                                          QT_POINTER_SIZE * 2, 16, QChar('0')));



    //    QStyleOptionProgressBar barOption;

    //    int height = 20;
    //    int marge  = 60;
    //    barOption.minimum = 0;
    //    barOption.maximum = 100;
    //    barOption.textAlignment = Qt::AlignCenter;
    //    barOption.textVisible = true;
    //    barOption.text = QString("Downloading %1").arg(45);
    //    barOption.rect.setLeft(boundingRect().left() + 50);
    //    barOption.rect.setRight(boundingRect().right() - 50);
    //    barOption.rect.setTop(boundingRect().top() + 50);
    //    barOption.rect.setHeight(20);
    //    barOption.progress =  54;

    //    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &barOption,painter);


    //    QFont font = QFont();
    //    font.setPixelSize(30);
    //    painter->setFont(font);
    //    painter->drawText(boundingRect(),Qt::AlignCenter,"TRACKS");

}

QVariant AbstractTrack::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
    {
        QPointF pos  = value.toPointF();
        pos.setX(0);
        if (pos.y() < 0)
            pos.setY(0);

        int median = pos.y() + boundingRect().height() / 2;
        int newSlot = trackList()->rowFromPixel(median);

        if (newSlot != mSlot && isSelected()){
            emit rowChanged(mSlot, newSlot);
        }
        return pos;

    }

    // This part manage selection. A native feature of QGraphicsItem
    if ( change == QGraphicsItem::ItemSelectedHasChanged)
    {
        // if selection == True, move the item on the top , to be not hiddable by other track
        if ( value.toBool())
            setZValue(10);
        else{
            setZValue(0);
        }
    }

    return QGraphicsObject::itemChange(change,value);
}


void AbstractTrack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    // default
    QGraphicsObject::mouseDoubleClickEvent(event);
}

void AbstractTrack::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    // Set movable only if cursor select the toolbar
    QGraphicsObject::mousePressEvent(event);

    QRect toolbarRect =  boundingRect().toRect();
    toolbarRect.setWidth(40);

    if (toolbarRect.contains( event->pos().toPoint()))
        setFlag(QGraphicsItem::ItemIsMovable,true);

    else
        setFlag(QGraphicsItem::ItemIsMovable,false);


}

void AbstractTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //Default
    QGraphicsObject::mouseMoveEvent(event);
}

void AbstractTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    setSelected(false);
    updatePositionFromSlot();
    QGraphicsObject::mouseReleaseEvent(event);
}


const QString &AbstractTrack::chromosom() const
{

    return trackList()->chromosom();

}

quint64 AbstractTrack::start() const
{
    return trackList()->start();

}

quint64 AbstractTrack::end() const
{
    return trackList()->end();

}

TrackListWidget *AbstractTrack::trackList() const
{
    return mTrackList;
}



}} // end namespace
