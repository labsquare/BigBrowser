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
}

QRectF AbstractTrack::boundingRect() const
{
    int w = scene()->views().first()->width();
    return QRect(0,0,w,40);

}

int AbstractTrack::height() const
{
    return boundingRect().height();
}

int AbstractTrack::row() const
{
    return mRow;
}

void AbstractTrack::setTrackList(TrackListWidget *parent)
{
    mTrackList = parent;
}

void AbstractTrack::setRow(int row)
{
    mRow = row;
}

void AbstractTrack::updatePositionFromRow()
{
    setPos(pos().x(), trackList()->rowToPixel(mRow));
}

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


    painter->drawText(boundingRect(),Qt::AlignCenter, QString::number(mRow));



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

        int moveRow = trackList()->rowFromPixel(pos.y());
        if (mRow != moveRow)
            emit rowChanged(mRow, moveRow);




        return pos;
    }

    if ( change == QGraphicsItem::ItemSelectedHasChanged)
    {
        if ( value.toBool())
            setZValue(10);
        else{
            setZValue(0);
            updatePositionFromRow();

        }
    }

    return QGraphicsObject::itemChange(change,value);
}


void AbstractTrack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"start anim";
    // "y" is One of the property of QGraphicsItem. See doc
    // Property are not variable.  A property has getter, setter AND changed signals


//    mAnimation->setDuration(4000);
//    mAnimation->setStartValue(trackList()->rowToPixel(mRow));
//    mAnimation->setEndValue(trackList()->rowToPixel(mRow+1));
//    mAnimation->setEasingCurve(QEasingCurve::OutBounce);
//    //    mAnimation->setLoopCount(4);

//    mAnimation->start();



}

void AbstractTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    setSelected(false);


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
