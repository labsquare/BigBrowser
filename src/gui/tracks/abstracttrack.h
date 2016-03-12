#ifndef ABSTRACTTRACK_H
#define ABSTRACTTRACK_H
#include <QGraphicsObject>
#include <QContiguousCache>
#include <QGraphicsSceneMouseEvent>
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
    TrackListWidget * trackList() const ;
    virtual QRectF boundingRect() const;
    int height() const;
    int row() const;

    void setTrackList(TrackListWidget * parent);

public Q_SLOTS:
    void setRow(int row);
    void updatePositionFromRow();

signals:
    void rowChanged(int before, int after);

protected:
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);


    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);




private:
    int mRow;
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;
    QPropertyAnimation * mAnimation;
    TrackListWidget * mTrackList;

};

}} // end namespace

#endif // ABSTRACTTRACK_H
