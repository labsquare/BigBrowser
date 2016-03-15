#include "tracklistwidget.h"
namespace big {
namespace gui {



TrackListWidget::TrackListWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);
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

    qDebug() << "AddTrack : " << track->slotIndex() << " " << xPos;

    connect(track,SIGNAL(heightChanged()),this,SLOT(updateTracksHeight()));
}








void TrackListWidget::switchSlotMode(bool slotModeON)
{
    mSlots.clear();
    foreach (AbstractTrack * track, mTracks)
    {
        // Save current slots ordering
        mSlots.append(track);

        // And notify all tracks
        track->setSlotMode(slotModeON);
    }

}

void TrackListWidget::slotReordering(AbstractTrack * draggedTrack)
{
    int yThreshold = draggedTrack->pos().y() + draggedTrack->height() / 2;

    // 1) Check cases where there is nothing to do
    int slotMatching = draggedTrack->matchSlot(yThreshold);
    if (slotMatching > 0                                                    // track over his hown slot
            || (draggedTrack->slotIndex() == 0 && slotMatching == -1)               // track slot 0 special case
            || (draggedTrack->slotIndex() == mSlots.count() && slotMatching == -2)) // track slot max special case
    {
        return;
    }

    int draggedTrackSlotIndex = 0;

    // 2) Find the slot over which the track is
    foreach (AbstractTrack * slot, mSlots)
    {
        slotMatching = slot->matchSlot(yThreshold);
        // Check if the track is over this slot
        if (slotMatching > 0)
        {
            if (slotMatching == 1)
            {
                // TopIn : Need to insert the draggedTrack's slot above this slot
                --draggedTrackSlotIndex;
                break;
            }
            else
            {
                // BotIn : Need to insert the draggedTrack's slot under this slot
                break;
            }
        }

        ++draggedTrackSlotIndex;
    }

    // We update view only if there is a change
    if (draggedTrack->slotIndex() != draggedTrackSlotIndex)
    {

        qDebug() << "slotReordering " << draggedTrack->slotIndex() << " > " << draggedTrackSlotIndex;

        // 3) Update Tracks slots
        mTracks.removeOne(draggedTrack);
        mTracks.insert(draggedTrackSlotIndex,draggedTrack);

        // 4) Notify all tracks to update their positions
        int idx = 0;
        int pos = 0;
        foreach (AbstractTrack * track, mTracks)
        {
            track->updateSlotPosition(idx, pos);
            ++idx;
            pos += track->height();
        }
    }
}

void TrackListWidget::updateTracksHeight()
{

    AbstractTrack * track = qobject_cast<AbstractTrack*>(sender());

    foreach ( AbstractTrack * t, mTracks)
    {
        if (t != track) {

          // Resize all tracks according emitter


        }


    }



}












void TrackListWidget::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    mChromosom = chromosom;
    mStart = start;
    mEnd = end;

    foreach ( AbstractTrack * track, mTracks)
    {
        track->update();
    }




}

void TrackListWidget::resizeEvent(QResizeEvent *event)
{
    // If I do not put 2000 .. I Do not have the scrollbar !
    mScene->setSceneRect(QRectF(0,0,event->size().width(),2000));


    QGraphicsView::resizeEvent(event);
}


}}
