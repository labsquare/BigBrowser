#ifndef TRACKSPANEL_H
#define TRACKSPANEL_H
#include <QWidget>
#include <QtWidgets>
#include "trackssettingscontainer.h"
namespace big {
namespace gui {

class TrackSettingsPanel : public QScrollArea
{
    Q_OBJECT
public:
    explicit TrackSettingsPanel(QWidget *parent = 0);
    void addWidget(QWidget * widget);

private:
    QWidget * mContent;
    QVBoxLayout * mContentLayout;
};


}}
#endif // TRACKSPANEL_H
