#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QStatusBar>
#include <QSlider>
#include <QFrame>
#include "selector.h"
namespace big {
namespace gui {
class StatusBar : public QFrame
{
    Q_OBJECT
public:
    StatusBar(QWidget * parent = 0);

public Q_SLOTS:
    void setSelection(int v);


private:
    QSlider * mSlider;
    core::Selector * select;


};
}}

#endif // STATUSBAR_H
