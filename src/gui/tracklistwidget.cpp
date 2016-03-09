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
    mTracks.append(track);
    scene()->addItem(track);



}

}}
