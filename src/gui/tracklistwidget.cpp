#include "tracklistwidget.h"

namespace big {
namespace gui {



TrackListWidget::TrackListWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);


    setBackgroundBrush(QColor(220,220,220));
}


QList<AbstractTrack *> TrackListWidget::tracks()
{
    return mTracks;
}


const QString &TrackListWidget::chromosom() const
{
    return mChromosom;
}

quint64 TrackListWidget::start() const
{
    return mStart;
}

quint64 TrackListWidget::end() const
{
    return mEnd;
}

int TrackListWidget::tracksHeight() const
{
    int total = 0;
    foreach (AbstractTrack * track, mTracks)
    {
        total += track->height();
    }
    return total;
}







void TrackListWidget::addTrack(AbstractTrack *track)
{
    track->setTrackList(this);
    track->setSlotIndex(mTracks.count());
    mTracks.append(track);
    scene()->addItem(track);

    int xPos = tracksHeight() - track->height();
    track->setPos(0, xPos);
    track->setSlotTop(xPos);

}


void TrackListWidget::switchSlotMode(bool slotModeON)
{
    foreach (AbstractTrack * track, mTracks)
    {
        // And notify all tracks
        track->setSlotMode(slotModeON);
    }
}

void TrackListWidget::slotReordering(AbstractTrack * draggedTrack)
{
    int yThreshold = draggedTrack->pos().y() + draggedTrack->height() / 2;


    int draggedTrackSlotIndex = -1;
    int slotIndex = -1;

    // Find the slot over which the track is
    foreach (AbstractTrack * slot, mTracks)
    {
        ++draggedTrackSlotIndex;
        int slotMatching = slot->matchSlot(yThreshold);
        if (slotMatching < 0) continue;

        // The track is over the slot

        // Case 1 : go above the current slot
        if (slotMatching == 2)
        {
            slotIndex = slot->slotIndex();
            draggedTrackSlotIndex++;
            break;
        }

        // Case 2 : take the position of the current slot
        slotIndex = slot->slotIndex();
        break;
    }

    // Cases where there is nothing to do (over his own slot, or outside of the grid)
    if (draggedTrack->slotIndex() == slotIndex || slotIndex == -1)
        return;

    if (slotIndex > draggedTrack->slotIndex())
    {
        draggedTrackSlotIndex--;
    }



    //qDebug() << "slotReordering " << draggedTrack->slotIndex() << " > " << draggedTrackSlotIndex;

    // Update Tracks slots
    mTracks.removeOne(draggedTrack);
    mTracks.insert(draggedTrackSlotIndex,draggedTrack);

    // Notify all tracks to update their positions
    int idx = 0;
    int pos = 0;
    foreach (AbstractTrack * track, mTracks)
    {
        track->updateSlotPosition(idx, pos);
        ++idx;
        pos += track->height();
    }
}


void TrackListWidget::updateSharedCursor(QPoint cursorPosition)
{
    foreach ( AbstractTrack * track, mTracks)
    {
        track->updateCursorPosition(cursorPosition);
    }
}


void TrackListWidget::updateTracksHeight()
{
    int pos = 0;
    foreach ( AbstractTrack * track, mTracks)
    {
        track->updateSlotTop(pos);
        pos += track->height();
    }
}


void TrackListWidget::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    mChromosom = chromosom;
    mStart = start;
    mEnd = end;

    foreach ( AbstractTrack * track, mTracks)
    {
        // qDebug() << "Update selection on track " << track->slotIndex() << " : " << mStart << " - " << mEnd;
        track->updateSelection();
    }

}

void TrackListWidget::resizeEvent(QResizeEvent *event)
{
    // If I do not put 2000 .. I Do not have the scrollbar !
    mScene->setSceneRect(QRectF(0,0,event->size().width(),2000));


    QGraphicsView::resizeEvent(event);
}


void TrackListWidget::trackScroll(int deltaX)
{
    quint64 min64 = 0; // to be opti
    quint64 distanceBase = end() - start(); // tobe opti
    float b2pCoeff = boundingRect().width() / distanceBase; // tobe opti

    qint64 deltaBase =  deltaX / b2pCoeff;
    quint64 newStartBase = start() + deltaBase;
    if (deltaX < 0 && newStartBase > start())
    {
        newStartBase = 0;
    }
    // same to do for max value
    //if (deltaX > 0 && )


    setSelection(mChromosom, newStartBase, newStartBase + distanceBase);
    emit selectionChanged(mChromosom, newStartBase, newStartBase + distanceBase);
}



}}
