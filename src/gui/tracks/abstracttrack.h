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
    // return the trackList parent of this Track Item
    TrackListWidget * trackList() const ;
    virtual QRectF boundingRect() const;
    // Return the height of the track
    int height() const;

    // Return the row of the track
    int row() const;

    // this methods is only called when you add item to the view
    void setTrackList(TrackListWidget * parent);

    // update position
    void setSlotPosition(int slotPosition);
    int slotPosition();
    void updatePosition(int position, bool withAnimation=true);
    QString title();

protected:
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);




private:
    int mSlotPosition;
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;
    QPropertyAnimation * mAnimation;
    TrackListWidget * mTrackList;


    int mHeight;
    int mTitle;

};

}} // end namespace

#endif // ABSTRACTTRACK_H
