#include "tracklistwidget.h"
namespace big {
namespace gui {
TrackListWidget::TrackListWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);

}

void TrackListWidget::addTrack(AbstractTrack *track)
{
    mTracks.append(track);
    scene()->addItem(track);


}

}}
