#include "abstracttrack.h"
#include <QPainter>
#include <QGraphicsScene>
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

void AbstractTrack::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    mChromosom = chromosom;
    mStart = start;
    mEnd = end;

}

const QString &AbstractTrack::chromosom() const
{
    return mChromosom;
}

quint64 AbstractTrack::start() const
{
    return mStart;
}

quint64 AbstractTrack::end() const
{
    return mEnd;
}



}} // end namespace
