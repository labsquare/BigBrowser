#include "tracksettingspanel.h"
namespace big {
namespace gui {
TrackSettingsPanel::TrackSettingsPanel(QWidget *parent) : QScrollArea(parent)
{
    mContent = new QWidget;
    mContentLayout = new QVBoxLayout;
    mContentLayout->setContentsMargins(0,0,0,0);
    mContentLayout->setSpacing(0);

    QWidget * spaceItem = new QWidget();
    spaceItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mContentLayout->addWidget(spaceItem);

    mContent->setLayout(mContentLayout);
    setWidgetResizable(true);
    setWidget(mContent);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TrackSettingsPanel::addWidget(QWidget *widget)
{
    TracksSettingsContainer * container = new TracksSettingsContainer;
    container->setWidget(widget);
    mContentLayout->insertWidget(0,container);

    mContent = new QWidget;
    mContent->setLayout(mContentLayout);


    setWidget(mContent);
}


}} // end namespace
