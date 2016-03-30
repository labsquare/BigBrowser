#include "trackswidget.h"

namespace big {
namespace gui {



TracksWidget::TracksWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);

    setBackgroundBrush(QColor(220,220,220));

    mSelectionBaseMax = 0;
    mSelectionScroll = 0;
    mSelectionP2B = C_BASE_MAX_PIXEL_WIDTH;
}

TracksWidget::~TracksWidget()
{
    qDeleteAll(mTracks);

}





QList<AbstractTrack *> TracksWidget::tracks()
{
    return mTracks;
}
const QString &TracksWidget::chromosom() const
{
    return selection().chromosom();
}
quint64 TracksWidget::start() const
{
    return selection().start();
}
quint64 TracksWidget::end() const
{
    return selection().end();
}


int TracksWidget::sharedCursorPosX() const
{
    return mSharedCursorPosX;
}
quint64 TracksWidget::sharedCursorPosB() const
{
    return mSharedCursorPosB;
}
int TracksWidget::sharedCursorBaseX() const
{
    return mSharedCursorBaseX;
}
int TracksWidget::sharedCursorBaseW() const
{
    return mSharedCursorBaseW;
}
int TracksWidget::selectionW() const
{
    return mSelectionW;
}
quint64 TracksWidget::selectionD() const
{
    return mSelectionD;
}
double TracksWidget::selectionScroll() const
{
    return mSelectionScroll;
}
int TracksWidget::trackContentStartX() const
{
    return C_TRACK_HANDLE_PIXEL_WIDTH;
}
void TracksWidget::setGenom(Genom *genom)
{
    mGenom = genom;
}

Genom *TracksWidget::genom()
{
    return mGenom;
}









int TracksWidget::tracksHeight() const
{
    int total = 0;
    foreach (AbstractTrack * track, mTracks)
    {
        total += track->height();
    }
    return total;
}

const Region &TracksWidget::selection() const
{
    return mSeletionB;
}

void TracksWidget::addTrack(AbstractTrack *track)
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
void TracksWidget::updateTracksHeight()
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

void TracksWidget::switchSlotMode(bool slotModeON)
{
    foreach (AbstractTrack * track, mTracks)
    {
        // And notify all tracks
        track->setSlotMode(slotModeON);
    }
}

void TracksWidget::slotReordering(AbstractTrack * draggedTrack)
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

void TracksWidget::updateSharedCursor(QPoint cursorPosition)
{
    // Update cursor data
    mSharedCursorPosX = cursorPosition.x() - C_TRACK_HANDLE_PIXEL_WIDTH;
    mSharedCursorPosB = pixelFrame2Base(mSharedCursorPosX);
    mSharedCursorBaseX = base2PixelFrame(mSharedCursorPosB);

    // notify all tracks
    emit cursorChanged(mSharedCursorPosX, mSharedCursorPosB, mSharedCursorBaseX, mSharedCursorBaseW);
}


void TracksWidget::setSelection(const Region &region)
{
    mSeletionB = region;
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

void TracksWidget::resizeEvent(QResizeEvent *event)
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


void TracksWidget::trackScroll(int deltaX)
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

        emit selectionChanged(Region(chromosom(), mSelectionStartB, mSelectionEndB));
        foreach ( AbstractTrack * track, mTracks)
        {
            track->updateSelection();
        }
    }
}




double TracksWidget::base2Coeff(quint64 base) const
{
    if (mSelectionBaseMax == 0)
    {
        return 0;
    }
    return ((double)base) / mSelectionBaseMax;
}

double TracksWidget::pixelFrame2Coeff(int pixel) const
{
    if (mSelectionBaseMax == 0)
    {
        return 0;
    }

    double globalPixelSize = mSelectionBaseMax * mSelectionP2B;
    double frameDelta = ((double)pixel) / globalPixelSize;
    return mSelectionScroll + frameDelta;
}

quint64 TracksWidget::pixelFrame2Base(int pixel) const
{
    return pixelFrame2Coeff(pixel) * mSelectionBaseMax;
}

int TracksWidget::base2PixelFrame(quint64 base) const
{
    return (base2Coeff(base) - mSelectionScroll) * mSelectionBaseMax * mSelectionP2B;
}



}}
