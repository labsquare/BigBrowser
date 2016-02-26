#include "statusbar.h"
#include <QSpacerItem>
StatusBar::StatusBar(QWidget * parent):
    QStatusBar(parent)
{
    mSlider = new QSlider(Qt::Horizontal);


    mSlider->setMaximumWidth(200);


  addPermanentWidget(mSlider);


}
