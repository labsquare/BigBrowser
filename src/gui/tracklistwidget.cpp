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
    mCursorScrollDelta = 0;
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


const int TrackListWidget::sharedCursorPosX() const
{
    return mCursorPositionX;
}
const quint64 TrackListWidget::sharedCursorPosB() const
{
    return mCursorPositionB;
}
const int TrackListWidget::sharedCursorBaseX() const
{
    return mCursorBaseX;
}
const int TrackListWidget::sharedCursorBaseW() const
{
    return mCursorBaseWidth;
}
const int TrackListWidget::trackContentWidth() const
{
    return mScene->width() - C_TRACK_HANDLE_PIXEL_WIDTH - (mHasScrollbar ? 20 : 0);
}
const int TrackListWidget::trackContentStartX() const
{
    return C_TRACK_HANDLE_PIXEL_WIDTH;
}
const int TrackListWidget::sharedCursorScrollDeltaX() const
{
    return mCursorScrollDelta;
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
    double delta = (mCursorPositionX - C_TRACK_HANDLE_PIXEL_WIDTH)/ mP2BCoeff; // need to convert in double for the "/" operator
    mCursorPositionB = start() +  delta;
    mCursorBaseWidth = qFloor(mP2BCoeff);

    // When zoom level is great (when we can see bases) to avoid display error due to rounded value
    // we recompute the CursorBaseX position according to the mCursorBaseWidth
    if (mCursorBaseWidth > 1)
    {
        quint64 deltaB = mCursorPositionB - start();
        mCursorBaseX = deltaB * mCursorBaseWidth + C_TRACK_HANDLE_PIXEL_WIDTH;
    }
    else
    {
        mCursorBaseX = mCursorPositionX;
    }

    // notify all tracks
    emit cursorChanged(mCursorPositionX, mCursorPositionB, mCursorBaseX, mCursorBaseWidth);
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
    float width = trackContentWidth(); // need to cast in float for precisions (see below)

    if (mSelectionDistance > 0)
    {
        // Ok, seems ok to use this distance
        mP2BCoeff = width / mSelectionDistance;
    }
    else
    {
        // To force the calculation of the distance according to the max zoom level,
        mP2BCoeff = C_BASE_MAX_PIXEL_WIDTH + 1;
    }

    // Check max zoom constraint : at max zoom level, base are drawn on C_MAX_BASE_PIXEL_WIDTH pixels
    if (mP2BCoeff > C_BASE_MAX_PIXEL_WIDTH)
    {
        mP2BCoeff = C_BASE_MAX_PIXEL_WIDTH;
        mSelectionDistance = width / mP2BCoeff;
        mSelectionEnd = mSelectionStart + mSelectionDistance;

    }
    mCursorBaseX = 0;
    mCursorBaseWidth = qRound(mP2BCoeff);

    // Need to notify all with the validated selection
    emit selectionValidated(chromosom, mSelectionStart, mSelectionEnd);

    foreach ( AbstractTrack * track, mTracks)
    {
        // qDebug() << "Update selection on track " << track->slotIndex() << " : " << mStart << " - " << mEnd;
        track->updateSelection();
    }
}

void TrackListWidget::resizeEvent(QResizeEvent *event)
{
    // Compute the best height for the tracklist scene
    int height = qMax(event->size().height(), tracksHeight());
    mHasScrollbar = height > event->size().height();
    mScene->setSceneRect(QRectF(0,0,event->size().width(), height));

    //setSelection(chromosom(), start(), end());
    QGraphicsView::resizeEvent(event);
}


void TrackListWidget::trackScroll(int deltaX)
{
    // Disable scroll (implementation in progress
    return;

    //mCursorBaseX += deltaX;
    mCursorScrollDelta -= deltaX;
    qDebug() << "mCursorBaseX : " << mCursorBaseX << " mCursorPositionX : " << mCursorPositionX << " mCursorScrollDelta : " << mCursorScrollDelta << " deltaX : " << deltaX;


    // recompute start & end according to the new mBasePositionX
    quint64 newStart = start();
    if (qAbs(mCursorScrollDelta) > mCursorBaseWidth)
    {
        float delta = mCursorScrollDelta;
        int step = delta / mCursorBaseWidth;
        newStart -= step;
        mCursorScrollDelta = mCursorScrollDelta - (step * mCursorBaseWidth);
    }
    /*
    if (deltaX < 0 && newStart > mSelectionStart)
    {
        newStart = 0;
    }
    else if (deltaX > 0 && newStart + mSelectionDistance > mSelectionMax)
    {
        newStart = mSelectionMax - mSelectionDistance;
    }
*/
    quint64 newEnd = newStart + mSelectionDistance;


    //qDebug() << " -> Start : " << start() << " => " << newStart ;

    if (newStart != start() && newEnd != end())
    {
        qDebug() << "SelectionChange : " << start() << " => " << newStart ;
        setSelection(mChromosom, newStart, newEnd);
        emit selectionValidated(mChromosom, newStart, newEnd);
    }
}



}}
