#include "statusbar.h"
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QPushButton>
namespace big {
namespace gui {
StatusBar::StatusBar(QWidget * parent):
    QFrame(parent),mGenom(0)
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

    connect(mSlider,SIGNAL(sliderMoved(int)),this,SLOT(sliderChanged()));



}

void StatusBar::setGenom(Genom *genom)
{
    mGenom = genom;
}


void StatusBar::sliderChanged()
{
    // WARNING
    ///TODO warning.. conversion int to quint64
    ///
//    quint64 value= mSlider->value();

//    mCurrentRegion*=1000;

//    emit selectionChanged(mCurrentRegion.chromosom(),
//                          mCurrentRegion.start(),
//                          mCurrentRegion.end());



    emit zoomChanged(mSlider->value());

}

void StatusBar::setSelection(const Region &region)
{
    mCurrentRegion = region;
    if (mGenom)
    {
        quint64 max = mGenom->chromosomLength(region.chromosom());
        mSlider->setRange(0,max);
        mSlider->setValue(region.length());
    }
}

}}
