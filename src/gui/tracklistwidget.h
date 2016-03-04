#ifndef TRACKLISTWIDGET_H
#define TRACKLISTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
namespace big {
namespace gui {
class TrackListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrackListWidget(QWidget *parent = 0);


private:
    QFrame * mLeftFrame;
    QFrame * mRightFrame;


};

}}
#endif // TRACKLISTWIDGET_H
