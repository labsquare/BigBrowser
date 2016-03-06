#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QStatusBar>
#include <QSlider>
#include <QFrame>
#include "genom.h"
namespace big {
using namespace core;
namespace gui {
class StatusBar : public QFrame
{
    Q_OBJECT
public:
    StatusBar(QWidget * parent = 0);


public Q_SLOTS:
    void updateSlider();
    void sliderChanged();

private:
    QSlider * mSlider;
    Genom   * mGenom;


};
}}

#endif // STATUSBAR_H
