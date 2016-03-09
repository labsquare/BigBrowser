#include "abstracttrack.h"
#include <QPainter>
#include <QGraphicsScene>
#include "tracklistwidget.h"
namespace big {
namespace gui {

AbstractTrack::AbstractTrack(QGraphicsItem *parent)
    :QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

QRectF AbstractTrack::boundingRect() const
{
    return QRect(0,0,800,100);

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
