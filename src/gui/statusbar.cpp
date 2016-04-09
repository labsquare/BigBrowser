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
    mCurrentRegion = Region();

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

    setDisabled(true);

}

void StatusBar::setGenom(Genom *genom)
{
    mGenom = genom;
}


void StatusBar::sliderChanged()
{
    qDebug()<<mCurrentRegion.length();


    quint64 value= mSlider->value();
    mCurrentRegion.scale(100000);
    emit selectionChanged(mCurrentRegion);




}

void StatusBar::setSelection(const Region &region)
{
    setDisabled(false);

    mCurrentRegion = region;
    if (mGenom)
    {
        quint64 max = mGenom->chromosomLength(region.chromosom());
        mSlider->setRange(0,max);
        mSlider->setValue(region.length());
    }
}

}}
