#ifndef TRACKLISTWIDGET_H
#define TRACKLISTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "abstracttrack.h"
namespace big {
namespace gui {
class TrackListWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TrackListWidget(QWidget *parent = 0);

    void addTrack(AbstractTrack * track);

public Q_SLOTS:


private:
QList<AbstractTrack*> mTracks;
QGraphicsScene * mScene;


};

}}
#endif // TRACKLISTWIDGET_H
