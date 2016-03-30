#include "tracklistwidget.h"

namespace big {
namespace gui {



TrackListWidget::TrackListWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);

    setBackgroundBrush(QColor(220,220,220));

    mSelectionBaseMax = 0;
    mSelectionScroll = 0;
    mSelectionP2B = C_BASE_MAX_PIXEL_WIDTH;
}

TrackListWidget::~TrackListWidget()
{
    qDeleteAll(mTracks);

}





QList<AbstractTrack *> TrackListWidget::tracks()
{
    return mTracks;
}
const QString &TrackListWidget::chromosom() const
{
    return mChromosom;
}
const quint64 TrackListWidget::start() const
{
    return mSelectionStartB;
}
const quint64 TrackListWidget::end() const
{
    return mSelectionEndB;
}


const int TrackListWidget::sharedCursorPosX() const
{
    return mSharedCursorPosX;
}
const quint64 TrackListWidget::sharedCursorPosB() const
{
    return mSharedCursorPosB;
}
const int TrackListWidget::sharedCursorBaseX() const
{
    return mSharedCursorBaseX;
}
const int TrackListWidget::sharedCursorBaseW() const
{
    return mSharedCursorBaseW;
}
const int TrackListWidget::selectionW() const
{
    return mSelectionW;
}
const quint64 TrackListWidget::selectionD() const
{
    return mSelectionD;
}
const double TrackListWidget::selectionScroll() const
{
    return mSelectionScroll;
}
const int TrackListWidget::trackContentStartX() const
{
    return C_TRACK_HANDLE_PIXEL_WIDTH;
}
void TrackListWidget::setGenom(Genom *genom)
{
    mGenom = genom;
}









const int TrackListWidget::tracksHeight() const
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



    connect(this,SIGNAL(cursorChanged(int, quint64, int, int)),
            track,SLOT(updateCursor(int, quint64, int, int)));

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





// ----------------------------------------------------------
// Slot Mode management : reordering tracks by drag&drop
// ----------------------------------------------------------

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







// ----------------------------------------------------------
// Tracks shared behavior : SharedCursor, Selection updates,
// and scrolling
// ----------------------------------------------------------

void TrackListWidget::updateSharedCursor(QPoint cursorPosition)
{
    // Update cursor data
    mSharedCursorPosX = cursorPosition.x() - C_TRACK_HANDLE_PIXEL_WIDTH;
    mSharedCursorPosB = pixelFrame2Base(mSharedCursorPosX);
    mSharedCursorBaseX = base2PixelFrame(mSharedCursorPosB);

    // notify all tracks
    emit cursorChanged(mSharedCursorPosX, mSharedCursorPosB, mSharedCursorBaseX, mSharedCursorBaseW);
}


void TrackListWidget::setSelection(const Region &region)
{
    mChromosom = region.chromosom();
    mSelectionBaseMax = 249250710; //mGenom->chromosomLength(chromosom);
    mSelectionStartB = qMin(region.start(),region.end());
    mSelectionEndB = qMax(region.start(),region.end());
    mSelectionD = mSelectionEndB - mSelectionStartB;

    if (mSelectionD > 0)
    {
        // Ok, seems ok to use this distance
        mSelectionP2B = mSelectionW / mSelectionD;
    }
    else
    {
        // To force the calculation of the distance according to the max zoom level,
        mSelectionP2B = C_BASE_MAX_PIXEL_WIDTH + 1;
    }

    // Check max zoom constraint : at max zoom level, base are drawn on C_MAX_BASE_PIXEL_WIDTH pixels
    if (mSelectionP2B > C_BASE_MAX_PIXEL_WIDTH)
    {
        mSelectionP2B = C_BASE_MAX_PIXEL_WIDTH;
        mSelectionD = mSelectionW / mSelectionP2B;
        mSelectionEndB = mSelectionStartB + mSelectionD;

    }
    //mSharedCursorBaseX = 0;
    mSelectionScroll = base2Coeff(mSelectionStartB);
    mSharedCursorBaseW = qRound(mSelectionP2B);

    // Need to notify all with the validated selection
//    emit selectionValidated(chromosom, mSelectionStartB, mSelectionEndB);

    foreach ( AbstractTrack * track, mTracks)
    {
        track->updateSelection();
    }
}

void TrackListWidget::resizeEvent(QResizeEvent *event)
{
    // Compute the best height for the tracklist scene
    int height = qMax(event->size().height(), tracksHeight());
    mHasScrollbar = height > event->size().height();
    mScene->setSceneRect(QRectF(0,0,event->size().width(), height));

    // Update track content width
    mSelectionW = mScene->width() - C_TRACK_HANDLE_PIXEL_WIDTH - (mHasScrollbar ? 20 : 0);

    // Need to redraw all
    setSelection(Region(chromosom(), start(), end()));
    QGraphicsView::resizeEvent(event);
}


void TrackListWidget::trackScroll(int deltaX)
{
    // scroll by adding delta to the current scroll coeff
    mSelectionScroll += deltaX / (mSelectionBaseMax * mSelectionP2B);

    // check min/max
    mSelectionScroll = qMax(mSelectionScroll, 0.0);
    mSelectionScroll = qMin(mSelectionScroll, base2Coeff(mSelectionBaseMax - mSelectionD));

    // update SelectionStart
    quint64 newSelectionStartB = mSelectionScroll * mSelectionBaseMax;

    // compute new pixel position of the SelectionStart
    mSelectionStartX = base2PixelFrame(newSelectionStartB);

    // notify that selection changed if needed
    if (newSelectionStartB != start())
    {
        mSelectionStartB = newSelectionStartB;
        mSelectionEndB = newSelectionStartB + mSelectionD;

        emit selectionValidated(mChromosom, mSelectionStartB, mSelectionEndB);
        foreach ( AbstractTrack * track, mTracks)
        {
            track->updateSelection();
        }
    }
}




const double TrackListWidget::base2Coeff(quint64 base) const
{
    if (mSelectionBaseMax == 0)
    {
        return 0;
    }
    return ((double)base) / mSelectionBaseMax;
}

const double TrackListWidget::pixelFrame2Coeff(int pixel) const
{
    if (mSelectionBaseMax == 0)
    {
        return 0;
    }

    double globalPixelSize = mSelectionBaseMax * mSelectionP2B;
    double frameDelta = ((double)pixel) / globalPixelSize;
    return mSelectionScroll + frameDelta;
}

const quint64 TrackListWidget::pixelFrame2Base(int pixel) const
{
    return pixelFrame2Coeff(pixel) * mSelectionBaseMax;
}

const int TrackListWidget::base2PixelFrame(quint64 base) const
{
    return (base2Coeff(base) - mSelectionScroll) * mSelectionBaseMax * mSelectionP2B;
}



}}
