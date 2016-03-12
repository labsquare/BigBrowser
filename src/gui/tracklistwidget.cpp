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
    track->setRow(mTracks.count());
    mTracks.append(track);
    scene()->addItem(track);
    track->setPos(0,track->boundingRect().height() * (mTracks.count()-1));

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

int TrackListWidget::rowToPixel(int row) const
{
    int y = 0;
    for (int i=0; i<row; ++i)
    {
        y += mTracks.at(i)->height();
    }
    return y;
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

}}
