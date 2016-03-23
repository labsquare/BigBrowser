#ifndef TRACKLISTWIDGET_H
#define TRACKLISTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QDebug>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QGraphicsScene>
#include "abstracttrack.h"

namespace big {
namespace gui {

class TrackListWidget : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QString chromosom READ chromosom )
    Q_PROPERTY(quint64 start READ start )
    Q_PROPERTY(quint64 end READ end )

public:
    explicit TrackListWidget(QWidget *parent = 0);

    //! Add a new track to the manager
    void addTrack(AbstractTrack * track);
    //! Remove a track from the manager
    void removeTrack(AbstractTrack * track);



    //! notify all tracks to switch or not in SlotMode (to allow reordoring of tracks)
    void switchSlotMode(bool slotModeON);
    //! check if the dragged track slot's position have changed, and update all slots positions if needed
    void slotReordering(AbstractTrack * draggedTrack);

    void updateSharedCursor(QPoint cursorPosition);


    //! Gets the list of tracks managed
    QList<AbstractTrack*> tracks();
    //! Gets the height of the tracklist
    int tracksHeight() const;


    const QString& chromosom() const;
    quint64 start() const;
    quint64 end() const;




public Q_SLOTS:
    void setSelection(const QString& chromosom, quint64 start, quint64 end);
    void updateTracksHeight();


Q_SIGNALS:
    void selectionChanged(const QString& chromosom, quint64 start, quint64 end);



protected:
    void resizeEvent(QResizeEvent * event);




private:

    // ----------------------------------------------------------
    // Business Data
    // ----------------------------------------------------------
    //! The name of the file where data are stored
    QString mChromosom;
    //! The base number where the selected region is starting
    quint64 mStart;
    //! The base number where the selected region is ending
    quint64 mEnd;



    // ----------------------------------------------------------
    // Drawing
    // ----------------------------------------------------------
    QGraphicsScene * mScene;


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
