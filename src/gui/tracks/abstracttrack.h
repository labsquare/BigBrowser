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

    //! Gets the trackList parent of this Track Item
    TrackListWidget * trackList() const ;
    //! Set the trackList parent of this Track Item
    void setTrackList(TrackListWidget * parent);


    //! Gets the height of the track
    int height() const;
    //! Set the height of the track
    void setHeight(int h);


    //! Sets the slot mode
    void setSlotMode(bool slotModeON);
    //! Gets if the slot mode is enable
    bool slotMode() const;
    //! Sets the slot index of the track
    int setSlotIndex(int slotIdx);
    //! Gets the slot index of the track
    int slotIndex() const;
    //! Sets the slot position of the track
    int setSlotTop(int slotTop);
    int slotTop() const;
    //! Update the slot of the track
    void updateSlotPosition(int slotIndex, int slotGhostTop);
    //! Return where is the provided position relating to the slot : -1="TopOut", 1="TopIn", 2="BotIn", -2="BotOut"
    int matchSlot(int yPosition);


    const QString& chromosom() const ;
    quint64 start() const;
    quint64 end() const;


    void goToSlotPosition();

    virtual QRectF boundingRect() const;
    virtual void paintRegion(QPainter *painter, const QString& chromosom, quint64 start, quint64 end);





protected:
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);





private:

    bool mSlotModeON;
    int mSlotIndex;
    int mSlotTop;
    int mSlotGhostTop;

    int mHeight;
    int mHeightMax;
    int mHeightMin;

    QPropertyAnimation * mAnimation;
    TrackListWidget * mTrackList;


};

}} // end namespace

#endif // ABSTRACTTRACK_H
