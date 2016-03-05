#ifndef TRACKLISTWIDGET_H
#define TRACKLISTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QGraphicsView>
namespace big {
namespace gui {
class TrackListWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TrackListWidget(QWidget *parent = 0);


private:



};

}}
#endif // TRACKLISTWIDGET_H
