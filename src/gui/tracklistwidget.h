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


    //! Return the base position of the given pixel in the Frame referential
    const quint64 pixelFrame2Base(int pixel) const;
    //! Return the pixel position in the Frame referential of the given base
    const int base2PixelFrame(quint64 base) const;
    //! Return the position of the base as a coeff between 0 and 1
    const double base2Coeff(quint64 base) const;
    //! Return the position of the pixel in the frame as a coeff between 0 and 1 indicating the position in the whole genom
    const double pixelFrame2Coeff(int pixel) const;



    //! Gets the list of tracks managed
    QList<AbstractTrack*> tracks();
    //! Gets the height of the tracklist
    const int tracksHeight() const;


    const QString& chromosom() const;
    const quint64 start() const;
    const quint64 end() const;

    const int trackContentStartX() const;

    const quint64 baseMax() const;


    // ----------------------------------------------------------
    // Selection properties
    // ----------------------------------------------------------
    const double selectionScroll() const;
    const int selectionW() const;
    const int selectionStartX();
    const quint64 selectionD() const;


    // ----------------------------------------------------------
    // Shared cursor properties
    // ----------------------------------------------------------
    const int sharedCursorPosX() const;
    const quint64 sharedCursorPosB() const;
    const int sharedCursorBaseX() const;
    const int sharedCursorBaseW() const;



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
    quint64 mSelectionStartB;
    //! The base number where the selected region is ending
    quint64 mSelectionEndB;

    quint64 mSelectionD;
    quint64 mSelectionBaseMax;

    Genom * mGenom;


    // ----------------------------------------------------------
    // Drawing
    // ----------------------------------------------------------
    QGraphicsScene * mScene;
    bool mHasScrollbar;


    double mSelectionP2B;
    double mSelectionScroll;
    float mSelectionW; // keep this width as a float as we do lot of division operation with it
    int mSelectionStartX;


    // ----------------------------------------------------------
    // SharedCursor properties
    // ----------------------------------------------------------
    //! The position (in pixel) of the cursor
    int mSharedCursorPosX;

    //! The position (in base) of the cursor
    quint64 mSharedCursorPosB;

    //! The width of the base in pixel
    int mSharedCursorBaseW;

    //! The delta (in pixel) of the first base displayed (start).
    int mSharedCursorBaseX;




    // ----------------------------------------------------------
    // Track management
    // ----------------------------------------------------------
    //! List of the track currently displayed
    QList<AbstractTrack*> mTracks;


};

}}
#endif // TRACKLISTWIDGET_H
