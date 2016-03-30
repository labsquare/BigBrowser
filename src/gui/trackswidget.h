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

/*!
 * \brief The TracksWidget class
 * Contains a list of track
 */

class TracksWidget : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QString chromosom READ chromosom )
    Q_PROPERTY(quint64 start READ start )
    Q_PROPERTY(quint64 end READ end )

public:
    const int C_BASE_MAX_PIXEL_WIDTH = 10;
    const int C_TRACK_HANDLE_PIXEL_WIDTH = 30;


    explicit TracksWidget(QWidget *parent = 0);
    ~TracksWidget();

    /*!
     * \brief addTrack
     * \param track
     */
    void addTrack(AbstractTrack * track);
    /*!
     * \brief removeTrack
     * \param track
     */
    void removeTrack(AbstractTrack * track);

    /*!
     * \brief setGenom
     * set genom pointer
     * \param genom
     */
    void setGenom(Genom * genom);

    /*!
     * \brief genom
     * \return genom pointer
     */
    Genom * genom();

    //! notify all tracks to switch or not in SlotMode (to allow reordoring of tracks)
    void switchSlotMode(bool slotModeON);
    //! check if the dragged track slot's position have changed, and update all slots positions if needed
    void slotReordering(AbstractTrack * draggedTrack);
    //! Manage the update of the cursor on all tracks
    void updateSharedCursor(QPoint cursorPosition);
    //! Manage the update of the selection on all tracks when scrolling is done on a track
    void trackScroll(int deltaX);


    //! Return the base position of the given pixel in the Frame referential
    quint64 pixelFrame2Base(int pixel) const;
    //! Return the pixel position in the Frame referential of the given base
    int base2PixelFrame(quint64 base) const;
    //! Return the position of the base as a coeff between 0 and 1
    double base2Coeff(quint64 base) const;
    //! Return the position of the pixel in the frame as a coeff between 0 and 1 indicating the position in the whole genom
    double pixelFrame2Coeff(int pixel) const;



    /*!
     * \brief tracks
     * \return list of AbstractTrack
     */
    QList<AbstractTrack*> tracks();

    /*!
     * \brief tracksHeight
     * \return total combined height of all track
     */
    int tracksHeight() const;

    /*!
     * \brief selection
     * Current selection
     * \see setSelection()
     * \return
     */
    const Region& selection() const;

    /*!
     * \brief chromosom
     * shortcut for selection()->chromosom()
     * \see selection()
     * \return
     */
    const QString& chromosom() const;
    /*!
     * \brief start
     * shortcut for selection()->start()
     * \see selection()
     * \return
     */
    quint64 start() const;
    /*!
     * \brief end
     * shortcut for selection()->end()
     * \return
     */
    quint64 end() const;

    int trackContentStartX() const;

    quint64 baseMax() const;


    // ----------------------------------------------------------
    // Selection properties
    // ----------------------------------------------------------
    double selectionScroll() const;
    int selectionW() const;
    int selectionStartX();
    quint64 selectionD() const;


    // ----------------------------------------------------------
    // Shared cursor properties
    // ----------------------------------------------------------
    int sharedCursorPosX() const;
    quint64 sharedCursorPosB() const;
    int sharedCursorBaseX() const;
    int sharedCursorBaseW() const;



public Q_SLOTS:
    /*!
      * \brief setSelection
      * Mandatory slot methods working with selectionRouter
      * \param region
      */
    void setSelection(const Region& region);

    void updateTracksHeight();


Q_SIGNALS:
    /*!
     * \brief selectionChanged
     * Mandatory signals methods working with selectionRouter
     * \param region
     */
    void selectionChanged(const Region& region);

    //! To notify tracks that the cursor position changed
    void cursorChanged(int posX, quint64 posB, int baseX, int baseW);



protected:
    void resizeEvent(QResizeEvent * event);



private:

    // ----------------------------------------------------------
    // Business Data
    // ----------------------------------------------------------
    Region mSeletionB;

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
