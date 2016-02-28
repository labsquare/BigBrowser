#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QStatusBar>
#include <QSlider>

namespace big {
namespace gui {
class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    StatusBar(QWidget * parent = 0);


private:
    QSlider * mSlider;


};
}}

#endif // STATUSBAR_H
