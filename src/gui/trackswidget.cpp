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
    mZoomLevelStep = 1.0/100; // 100 levels of zoom
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


float TracksWidget::sharedCursorPosX() const
{
    return mSharedCursorPosX;
}
quint64 TracksWidget::sharedCursorPosB() const
{
    return mSharedCursorPosB;
}
float TracksWidget::sharedCursorBaseX() const
{
    return mSharedCursorBaseX;
}
float TracksWidget::sharedCursorBaseW() const
{
    return mSharedCursorBaseW;
}
float TracksWidget::selectionW() const
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
float TracksWidget::trackContentStartX() const
{
    return C_TRACK_HANDLE_PIXEL_WIDTH;
}
void TracksWidget::setGenom(Genom *genom)
{
    mGenom = genom;
    mZoomLevelStep = 0;
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
    return mSeletion;
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



    connect(this,SIGNAL(cursorChanged(float, quint64, float, float)),
            track,SLOT(updateCursor(float, quint64, float, float)));

}
void TracksWidget::updateTracksHeight()
{
    float pos = 0;
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
    float yThreshold = draggedTrack->pos().y() + draggedTrack->height() / 2;


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
    float pos = 0;
    foreach (AbstractTrack * track, mTracks)
    {
        track->updateSlotPosition(idx, pos);
        ++idx;
        pos += track->height();
    }
}


void TracksWidget::updateZoomLevelStep()
{
    // compute zoom level step step
    double minP2B = mSelectionW / mSelectionBaseMax;
    double maxP2B = C_BASE_MAX_PIXEL_WIDTH;

    // Step for 100 zoom levels
    mZoomLevelStep = (maxP2B - minP2B) / 100.0;
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
    mSeletion = region;
    mSelectionBaseMax = 249250710; //mGenom->chromosomLength(chromosom);
    mSelectionStartB = qMin(region.start(),region.end());
    mSelectionEndB = qMax(region.start(),region.end());
    mSelectionD = mSelectionEndB - mSelectionStartB;

    // Compute zoom level if needed
    if (mZoomLevelStep == 0)
    {
        updateZoomLevelStep();
    }


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

    foreach ( AbstractTrack * track, mTracks)
    {
        track->updateSelection();
    }
}

void TracksWidget::resizeEvent(QResizeEvent *event)
{
    // Compute the best height for the tracklist scene
    float height = qMax(event->size().height(), tracksHeight());
    mHasScrollbar = height > event->size().height();
    mScene->setSceneRect(QRectF(0,0,event->size().width(), height));

    // Update track content width
    mSelectionW = mScene->width() - C_TRACK_HANDLE_PIXEL_WIDTH - (mHasScrollbar ? 20 : 0);

    // Need to redraw all
    setSelection(Region(chromosom(), start(), end()));
    QGraphicsView::resizeEvent(event);
}


void TracksWidget::trackScroll(float deltaX)
{
    qDebug() << "trackScroll " << deltaX;

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

        mSeletion.setStart(mSelectionStartB);
        mSeletion.setEnd(mSelectionEndB);

        emit selectionChanged(Region(chromosom(), mSelectionStartB, mSelectionEndB));
        foreach ( AbstractTrack * track, mTracks)
        {
            track->updateSelection();
        }
    }
}

void TracksWidget::trackZoom(float deltaZ)
{
    // get coeff delta (as mouse wheel delta can be have different behavior according to the hardware
    double zoomC = ( (deltaZ > 0) ? 1 : -1) * (1.0/10000);
    qDebug() << "trackZoom " << zoomC << " mZoomLevelStep = " << mZoomLevelStep;

    double cursorC = pixelFrame2Coeff(mSharedCursorPosX);
    double startC = pixelFrame2Coeff(0);
    double endC = pixelFrame2Coeff(mSelectionW);
    double distanceC = endC - startC;
    qDebug() << " - cursorC : " << cursorC << " startC : " << startC;


    double newDistanceC = distanceC + zoomC;
    double newP2B = mSelectionW / (newDistanceC * mSelectionBaseMax);

    qDebug() << " - mSelectionP2B : " << mSelectionP2B << " -> newP2B : " << newP2B << " mSelectionScroll : " << mSelectionScroll;
    mSelectionP2B = newP2B;
    double globalPixelSize = mSelectionBaseMax * mSelectionP2B;
    float newCursorX = (cursorC - mSelectionScroll) * globalPixelSize;
    qDebug() << " - cursorC : " << cursorC << " scroll dX : " << mSharedCursorPosX - newCursorX;
    trackScroll(mSharedCursorPosX - newCursorX);
}




double TracksWidget::base2Coeff(quint64 base) const
{
    if (mSelectionBaseMax == 0)
    {
        return 0;
    }
    return ((double)base) / mSelectionBaseMax;
}

double TracksWidget::pixelFrame2Coeff(float pixel) const
{
    if (mSelectionBaseMax == 0)
    {
        return 0;
    }

    double globalPixelSize = mSelectionBaseMax * mSelectionP2B;
    double frameDelta = ((double)pixel) / globalPixelSize;
    return mSelectionScroll + frameDelta;
}

quint64 TracksWidget::pixelFrame2Base(float pixel) const
{
    return pixelFrame2Coeff(pixel) * mSelectionBaseMax;
}

float TracksWidget::base2PixelFrame(quint64 base) const
{
    return (base2Coeff(base) - mSelectionScroll) * mSelectionBaseMax * mSelectionP2B;
}



}}
