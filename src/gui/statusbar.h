#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QStatusBar>
#include <QSlider>
#include <QFrame>
#include "genom.h"
#include "selection.h"
namespace big {
using namespace core;
namespace gui {
class StatusBar : public QFrame
{
    Q_OBJECT
public:
    StatusBar(QWidget * parent = 0);
    void setGenom(Genom * genom);


public Q_SLOTS:
    void setSelection(const Selection& selection );
Q_SIGNALS:
    void zoomChanged(int value);
    void selectionChanged(const Selection& selection);

protected Q_SLOTS:
    void sliderChanged();


private:
    QSlider * mSlider;
    Genom   * mGenom;
    Selection mCurrentRegion;


};
}}

#endif // STATUSBAR_H
