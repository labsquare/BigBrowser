#include "tracklistwidget.h"
namespace big {
namespace gui {
TrackListWidget::TrackListWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);

    setResizeAnchor(QGraphicsView::NoAnchor);
    //    setTransformationAnchor(QGraphicsView::NoAnchor	);

    mScene->setSceneRect(rect());


}

void TrackListWidget::addTrack(AbstractTrack *track)
{
    track->setParent(track);
    mTracks.append(track);
    scene()->addItem(track);

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

void TrackListWidget::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    mChromosom = chromosom;
    mStart = start;
    mEnd = end;
}

}}
