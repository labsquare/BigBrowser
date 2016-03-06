#include "statusbar.h"
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QPushButton>
#include "selector.h"
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


select =  new core::Selector;


connect(mSlider,SIGNAL(valueChanged(int)),this,SLOT(setSelection(int)));


}

void StatusBar::setSelection(int v)
{
    select->setStart(v);
}
}}
