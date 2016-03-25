#include "trackssettingscontainer.h"
namespace big {
namespace gui {
TracksSettingsContainer::TracksSettingsContainer(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setSpacing( 0 );
    layout->setContentsMargins( 0, 0, 0, 0 );

    mHeader = new TrackSettingsHeader;

    layout->addWidget(mHeader);

    //    mToolButton = new QToolButton;
    //    mTitleLabel = new QLabel("no title");
    //    mIconLabel = new QLabel;
    //    mIconLabel->setFixedSize(16,16);
    //    mToolButton->setArrowType(Qt::DownArrow);
    //    mToolButton->setCheckable(true);
    //    mToolButton->setChecked(true);
    //    headerLayout->addWidget(mIconLabel);
    //    headerLayout->addWidget(mTitleLabel);
    //    headerLayout->addWidget(mToolButton);
    //    //    header->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //    headerLayout->setContentsMargins(2,0,0,0);


    mContent = new QWidget;
    QVBoxLayout * contentLayout = new QVBoxLayout;
    contentLayout->setContentsMargins(0,0,0,0);
    mContent->setLayout(contentLayout);

    layout->addWidget(mContent);

    setLayout( layout );

    // connect(mToolButton,SIGNAL(toggled(bool)),this,SLOT(collapse(bool)));

    connect(mHeader,SIGNAL(expandChanged(bool)),this,SLOT(expand(bool)));
    mContent->setVisible(false);
}

void TracksSettingsContainer::setWidget(QWidget *widget)
{
    mContent->layout()->addWidget(widget);
    //widget->setStyleSheet("QWidget {background-color:lightgray}");
    //    setTitle(widget->windowTitle());
    //    setIcon(widget->windowIcon());
}

void TracksSettingsContainer::expand(bool expand)
{
    mContent->setVisible(!expand);
}

void TracksSettingsContainer::collapse(bool collapse)
{
    mContent->setVisible(collapse);
}

}} // end namespace
