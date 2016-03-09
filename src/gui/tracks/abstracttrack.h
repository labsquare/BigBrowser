#ifndef ABSTRACTTRACK_H
#define ABSTRACTTRACK_H
#include <QGraphicsObject>
#include <QContiguousCache>
namespace big {
namespace gui {
class TrackListWidget;
class AbstractTrack : public QGraphicsObject
{
    Q_OBJECT
public:
    AbstractTrack(QGraphicsItem * parent = 0);

protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    const QString& chromosom() const ;
    quint64 start() const;
    quint64 end() const;


    TrackListWidget * trackView() const;



private:
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;

};

}} // end namespace

#endif // ABSTRACTTRACK_H
