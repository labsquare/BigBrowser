#include "abstracttrack.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include "tracklistwidget.h"
namespace big {
namespace gui {

AbstractTrack::AbstractTrack(QGraphicsItem *parent)
    :QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF AbstractTrack::boundingRect() const
{
    int w = scene()->views().first()->width();
    return QRect(0,0,w,200);

}

void AbstractTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(Qt::red));
    painter->setBrush(QBrush(Qt::blue));
    painter->drawRect(boundingRect());

    QFont font = QFont();
    font.setPixelSize(30);
    painter->setFont(font);
    painter->drawText(boundingRect(),Qt::AlignCenter,"TRACKS");

}

QVariant AbstractTrack::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
    {

       QPointF pos  = value.toPointF();
       pos.setX(0);

       if (pos.y() < 0)
           pos.setY(0);

       return pos;
    }

    return QGraphicsObject::itemChange(change,value);
}


const QString &AbstractTrack::chromosom() const
{

    return trackView()->chromosom();

}

quint64 AbstractTrack::start() const
{
    return trackView()->start();

}

quint64 AbstractTrack::end() const
{
    return trackView()->end();

}

TrackListWidget *AbstractTrack::trackView() const
{
    TrackListWidget * view = qobject_cast<TrackListWidget*>(parent());
    return view;
}



}} // end namespace
