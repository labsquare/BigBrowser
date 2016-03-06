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
    void setGenom(Genom * genom);


public Q_SLOTS:
    void setSelection(const QString& chromosom, quint64 start, quint64 end);

Q_SIGNALS:
    void zoomChanged(int value);

protected Q_SLOTS:
    void sliderChanged();


private:
    QSlider * mSlider;
    Genom   * mGenom;
    Region mCurrentRegion;


};
}}

#endif // STATUSBAR_H
