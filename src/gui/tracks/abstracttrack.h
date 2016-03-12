#ifndef ABSTRACTTRACK_H
#define ABSTRACTTRACK_H
#include <QGraphicsObject>
#include <QContiguousCache>
#include <QPropertyAnimation>
namespace big {
namespace gui {
class TrackListWidget;
class AbstractTrack : public QGraphicsObject
{
    Q_OBJECT
public:
    AbstractTrack(QGraphicsItem * parent = 0);
    const QString& chromosom() const ;
    quint64 start() const;
    quint64 end() const;
    TrackListWidget * trackView() const;
    virtual QRectF boundingRect() const;

protected:
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);





private:
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;
    QPropertyAnimation * mAnimation;

};

}} // end namespace

#endif // ABSTRACTTRACK_H
