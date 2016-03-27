#ifndef TRACKLISTWIDGET_H
#define TRACKLISTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QDebug>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QGraphicsScene>
#include "genom.h"
#include "abstracttrack.h"

namespace big {
namespace gui {
using namespace core;
class TrackListWidget : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QString chromosom READ chromosom )
    Q_PROPERTY(quint64 start READ start )
    Q_PROPERTY(quint64 end READ end )

public:
    const int C_BASE_MAX_PIXEL_WIDTH = 10;
    const int C_TRACK_HANDLE_PIXEL_WIDTH = 30;


    explicit TrackListWidget(QWidget *parent = 0);
    ~TrackListWidget();

    //! Add a new track to the manager
    void addTrack(AbstractTrack * track);
    //! Remove a track from the manager
    void removeTrack(AbstractTrack * track);

    void setGenom(Genom * genom);



    //! notify all tracks to switch or not in SlotMode (to allow reordoring of tracks)
    void switchSlotMode(bool slotModeON);
    //! check if the dragged track slot's position have changed, and update all slots positions if needed
    void slotReordering(AbstractTrack * draggedTrack);
    //! Manage the update of the cursor on all tracks
    void updateSharedCursor(QPoint cursorPosition);
    //! Manage the update of the selection on all tracks when scrolling is done on a track
    void trackScroll(int deltaX);

    //! Gets the list of tracks managed
    QList<AbstractTrack*> tracks();
    //! Gets the height of the tracklist
    int tracksHeight() const;


    const QString& chromosom() const;
    quint64 start() const;
    quint64 end() const;
    void setSelectionMax(quint64 max);

    const int sharedCursorPosX() const;
    const quint64 sharedCursorPosB() const;
    const int sharedCursorBaseX() const;
    const int sharedCursorBaseW() const;
    const int trackContentWidth() const;
    const int trackContentStartX() const;
    const int sharedCursorScrollDeltaX() const;



public Q_SLOTS:
    void setSelection(const QString& chromosom, quint64 start, quint64 end);
    void updateTracksHeight();


Q_SIGNALS:

    void selectionValidated(const QString& chromosom, quint64 start, quint64 end);

    //! To notify tracks that the cursor position changed
    void cursorChanged(int posX, quint64 posB, int baseX, int baseW);



protected:
    void resizeEvent(QResizeEvent * event);



private:

    // ----------------------------------------------------------
    // Business Data
    // ----------------------------------------------------------
    //! The name of the file where data are stored
    QString mChromosom;
    //! The base number where the selected region is starting
    quint64 mSelectionStart;
    //! The base number where the selected region is ending
    quint64 mSelectionEnd;

    quint64 mSelectionDistance;
    quint64 mSelectionMax;

    Genom * mGenom;


    // ----------------------------------------------------------
    // Drawing
    // ----------------------------------------------------------
    QGraphicsScene * mScene;
    float mP2BCoeff;
    bool mHasScrollbar;


    // ----------------------------------------------------------
    // SharedCursor properties
    // The cursor position/selection is shared by all tracks via the tracklist wirdget
    // ----------------------------------------------------------
    //! The position (in pixel) of the cursor
    int mCursorPositionX;

    //! The position (in base) of the cursor
    quint64 mCursorPositionB;

    //! The width of the base in pixel
    int mCursorBaseWidth;

    //! The delta (in pixel) of the first base displayed (start).
    int mCursorBaseX;

    int mCursorScrollDelta;

    // ----------------------------------------------------------
    // Track management
    // ----------------------------------------------------------
    //! List of the track currently displayed
    QList<AbstractTrack*> mTracks;

    //! The position of the cursor is shared by all tracks
    int mTrackCursorPosition;


};

}}
#endif // TRACKLISTWIDGET_H
