#include "statusbar.h"
#include <QSpacerItem>

namespace big {
namespace gui {
StatusBar::StatusBar(QWidget * parent):
    QStatusBar(parent)
{
    mSlider = new QSlider(Qt::Horizontal);


    mSlider->setMaximumWidth(200);


    addPermanentWidget(mSlider);


}
}}
