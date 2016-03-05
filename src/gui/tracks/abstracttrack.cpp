#include "abstracttrack.h"
#include <QPainter>
namespace big {
namespace gui {

AbstractTrack::AbstractTrack(QGraphicsItem *parent)
    :QGraphicsObject(parent)
{

}

QRectF AbstractTrack::boundingRect() const
{
   return QRect(10,10,100,100);

}

void AbstractTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(Qt::red));
    painter->drawRect(boundingRect());

}


}} // end namespace
