#include "abstracttrack.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QApplication>
#include <QGraphicsScene>
#include <QStyleOptionProgressBar>
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
    setHeight(qrand()%100 + 40);
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

    painter->setPen(QPen(Qt::lightGray));
    if (isSelected())
        painter->setBrush(Qt::red);

    else
        painter->setBrush(Qt::blue);

    painter->drawRect(boundingRect());


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
    // "y" is One of the property of QGraphicsItem. See doc
    // Property are not variable.  A property has getter, setter AND changed signals


    //    mAnimation->setDuration(4000);
    //    mAnimation->setStartValue(trackList()->rowToPixel(mRow));
    //    mAnimation->setEndValue(trackList()->rowToPixel(mRow+1));
    //    mAnimation->setEasingCurve(QEasingCurve::OutBounce);
    //    //    mAnimation->setLoopCount(4);

    //    mAnimation->start();

    QGraphicsObject::mouseDoubleClickEvent(event);



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
