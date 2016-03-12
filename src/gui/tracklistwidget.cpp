#include "tracklistwidget.h"
namespace big {
namespace gui {
TrackListWidget::TrackListWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);


    //    setResizeAnchor(QGraphicsView::NoAnchor);
    //    setTransformationAnchor(QGraphicsView::NoAnchor	);

    //    mScene->setSceneRect(rect());



}

void TrackListWidget::addTrack(AbstractTrack *track)
{


    track->setTrackList(this);
    mTracks.append(track);
    scene()->addItem(track);
    int pos = 0;
    foreach (AbstractTrack *track, mTracks)
    {
        pos += track->height();
    }
    track->setPos(0,pos - track->height());
    track->setSlotPosition(pos - track->height());

    //rearrange(track, false);

    //setPos(0,track->boundingRect().height() * (mTracks.count()-1));

    //connect(track,SIGNAL(rowChanged(int,int)),this,SLOT(rearrage(int,int)));

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



QList<AbstractTrack *> TrackListWidget::tracks()
{
    return mTracks;
}


void TrackListWidget::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    mChromosom = chromosom;
    mStart = start;
    mEnd = end;
}

void TrackListWidget::resizeEvent(QResizeEvent *event)
{
    // If I do not put 2000 .. I Do not have the scrollbar !
    mScene->setSceneRect(QRectF(0,0,event->size().width(),2000));
    QGraphicsView::resizeEvent(event);
}

void TrackListWidget::rearrange(AbstractTrack * movingTrack, bool withAnimation )
{
    // Compute the threshold for the Y reaarangement
    //qDebug() << "REARRANGE tracks (" << mTracks.count() << ") called by " << movingTrack->title();


    int currentPos = 0;

    bool needToRearrange = false;

    // First loop : reorder
    for (int idx=0; idx < mTracks.count(); idx++) // AbstractTrack * track , mTracks)
    {
        AbstractTrack * track = mTracks[idx];
        int yThreshold = movingTrack->pos().y() + movingTrack->height() / 2;
        int yMin = currentPos;
        int yMax = yMin + track->height();


        //qDebug() << " - " << idx << "(" << currentPos << " [" << yThreshold << "]";


        if (yThreshold >=yMin && yThreshold <= yMax)
        {
            //qDebug() << "   movedTrack [" << track->title() << "] go to the top position : " << idx << "(" << currentPos << ")";
            // Put the dragged track at its new place
            mTracks.removeOne(movingTrack);
            mTracks.insert(idx, movingTrack);

            needToRearrange = true;
            break;
        }

        //qDebug() << "   track [" << track->title() << "] over its slot : " <<idx << "(" << currentPos << ")";
        currentPos += track->height();
        continue;
    }

    // Second loop : rearrange items
    //qDebug() << "result : ";
    currentPos = 0;
    foreach (AbstractTrack * track, mTracks)
    {
        //qDebug() << "   track [" << track->title() << "] go to the position : "  << currentPos;
        track->updatePosition(currentPos, withAnimation);
        currentPos += track->height();
    }
    //qDebug() << "";

    return;
}

}}
