#include "statusbar.h"
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QPushButton>
namespace big {
namespace gui {
StatusBar::StatusBar(QWidget * parent):
    QFrame(parent)
{
    mSlider = new QSlider(Qt::Horizontal);

    QWidget * leftWidget = new QWidget();
    leftWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget * rightWidget = new QWidget();
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(leftWidget);
    hLayout->addWidget(mSlider);
    hLayout->addWidget(rightWidget);
    hLayout->setContentsMargins(0,0,0,0);

    setLayout(hLayout);


   setMaximumHeight(20);






}
}}
