#include "tracklistwidget.h"

namespace big {
namespace gui {



TrackListWidget::TrackListWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);

    setBackgroundBrush(QColor(220,220,220));

    // Todo @Sacha : maxValue for the end of the selection must be shared with the tracklist to "bound" the scrolling into tracks.
    mSelectionMax = 249250617;
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
    return mSelectionStart;
}

quint64 TrackListWidget::end() const
{
    return mSelectionEnd;
}

void TrackListWidget::setSelectionMax(quint64 max)
{
    mSelectionMax = max;
}


const int TrackListWidget::sharedCursorX() const
{
    return mCursorPositionX;
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
    track->setIndex(mTracks.count());
    mTracks.append(track);
    scene()->addItem(track);

    int xPos = tracksHeight() - track->height();
    track->setPos(0, xPos);
    track->setTop(xPos);

}

void TrackListWidget::setGenom(Genom *genom)
{
    mGenom = genom;
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
            slotIndex = slot->index();
            draggedTrackSlotIndex++;
            break;
        }

        // Case 2 : take the position of the current slot
        slotIndex = slot->index();
        break;
    }

    // Cases where there is nothing to do (over his own slot, or outside of the grid)
    if (draggedTrack->index() == slotIndex || slotIndex == -1)
        return;

    if (slotIndex > draggedTrack->index())
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
    // Update cursor data
    mCursorPositionX = cursorPosition.x();
    mCursorPositionB = mCursorPositionX * mP2BCoeff;
    mBaseWidth = qFloor(mP2BCoeff);

    // When zoom level is great (when we can see bases) we have to take in account
    // a deltaX to manage smooth scrolling
    if (mBaseWidth > 1)
    {
        // Todo
        // mBasePositionX;
    }

    // notify all tracks
    emit cursorChanged(mCursorPositionX, mCursorPositionB, mBasePositionX, mBaseWidth);
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
    mSelectionStart = qMin(start, end);
    mSelectionEnd = qMax(start, end);
    mSelectionDistance = mSelectionEnd - mSelectionStart;
    mP2BCoeff = (mSelectionDistance > 0) ? mScene->width() / mSelectionDistance : 0;

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
    mP2BCoeff = (mSelectionDistance > 0) ? mScene->width() / mSelectionDistance : 0;

    QGraphicsView::resizeEvent(event);
}


void TrackListWidget::trackScroll(int deltaX)
{
    qint64 deltaBase =  deltaX / mP2BCoeff;
    quint64 newStart = mSelectionStart + deltaBase;

    if (deltaX < 0 && newStart > mSelectionStart)
    {
        newStart = 0;
    }
    else if (deltaX > 0 && newStart + mSelectionDistance > mSelectionMax)
    {
        newStart = mSelectionMax - mSelectionDistance;
    }

    quint64 newEnd = newStart + mSelectionDistance;


    setSelection(mChromosom, newStart, newEnd);
    emit selectionChanged(mChromosom, newStart, newEnd);
}



}}
