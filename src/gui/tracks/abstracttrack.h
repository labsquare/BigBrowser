#ifndef ABSTRACTTRACK_H
#define ABSTRACTTRACK_H
#include <QGraphicsObject>
#include <QContiguousCache>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

namespace big {
namespace gui {
class TrackListWidget;


class AbstractTrack : public QGraphicsObject
{
    Q_OBJECT
public:

    AbstractTrack(QGraphicsItem * parent = 0);
    ~AbstractTrack();

    /*!
     * \brief trackList
     * \return the parent trackList
     */
    TrackListWidget * trackList() const ;
    /*!
     * \brief setTrackList
     * Set the trackList parent of this Track Item
     * \param parent
     */
    void setTrackList(TrackListWidget * parent);

    /*!
     * \brief height
     * \return track's height
     */
    int height() const;

    /*!
     * \brief setHeight
     * set Track Height
     * \param h
     */
    void setHeight(int h);

    /*!
     * \brief chromosom
     * \return trackList->chromosom()
     */
    const QString& chromosom() const ;

    /*!
     * \brief start
     * \return trackList->start()
     */
    quint64 start() const;

    /*!
     * \brief end
     * \return trackList->end()
     */
    quint64 end() const;


    /*!
     * \brief updateSelection
     * This methods is called when parent list view received new selection
     */
    virtual void updateSelection();

    /*!
     * \brief isTrackSelected
     * Indicates if the track is currently selected (manipulated via handle) or not. Do not used the QGraphicsObject::isSelected
     * \return
     */
    bool isTrackSelected() const;
    void setTrackSelected(bool selected);


    /*! \brief isResizable
    Indicates if the track can be resized by the user
     * \return
     */
    bool isResizable() const;
    void setResizable(bool isResizable);

    /*!
     * \brief setIndex
     * Gets the slot index of the track
     * \param slotIdx
     */
    void setIndex(int slotIdx);
    int index() const;

    /*!
     * \brief setTop
     * Sets the slot position of the track
     * \param slotTop
     */
    void setTop(int slotTop);
    int top() const;


    // @OLIVIER : I think thos methods should not be public.
    // If only TrackviewList should access those methods, you may see "friends".

    //! Sets the slot mode
    void setSlotMode(bool slotModeON);
    //! Gets if the slot mode is enable
    bool slotMode() const;
    //! Sets the slot index of the track

    //! Update the slot of the track
    void updateSlotPosition(int index, int slotGhostTop);
    //! Update the slot position of the track (only used when slot top pos changed due to the resizing of a track)
    void updateSlotTop(int slotTop);
    //! Return where is the provided position relating to the slot : -1="TopOut", 1="TopIn", 2="BotIn", -2="BotOut"
    int matchSlot(int yPosition);






    //! The boundaries of the whole track (track's handle + track's content + tracklist's scrollbar hover the tracks)
    virtual QRectF boundingRect() const;

    //! The boundaries of the area availables to draw the content
    virtual QRectF boundingRectContent() const;



public Q_SLOTS:
    //! To update the cursor position & redraw the track
    void updateCursor(int posX,quint64 posB, int baseX, int baseW);

protected:
    void goToSlotPosition();

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual void paintRegion(QPainter *painter, const QString& chromosom, quint64 start, quint64 end);
    virtual void paintCursorLayer(QPainter * painter);

    //virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);





    //! Content cache image : Keeping it in memory to avoid to redraw it too often
    QImage mContentCache;

    //! The tracklist of which the track is the child
    TrackListWidget * mTrackList;

    //! The position (in pixel) of the cursor
    int mCursorPosition;

private:
    int mHeight;
    int mHeightMax;
    int mHeightMin;

    bool mIsResizable;
    bool mIsSelected;
    bool mSlotModeON;
    int mSlotIndex;
    int mSlotTop;
    int mSlotGhostTop;


    QPropertyAnimation *        mAnimation;
    QGraphicsDropShadowEffect * mShadowEffect;




};

}} // end namespace

#endif // ABSTRACTTRACK_H
