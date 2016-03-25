#include "trackssettingscontainer.h"
namespace big {
namespace gui {
TracksSettingsContainer::TracksSettingsContainer(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setSpacing( 0 );
    layout->setContentsMargins( 0, 0, 0, 0 );

    mHeader    = new TrackSettingsHeader;
    mAnimation = new QVariantAnimation(this);

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


    mContentLayout = new QVBoxLayout;
    mContentLayout->setContentsMargins(0,0,0,0);



    layout->addLayout(mContentLayout);
    setLayout( layout );

    // connect(mToolButton,SIGNAL(toggled(bool)),this,SLOT(collapse(bool)));

    connect(mHeader,SIGNAL(expandChanged(bool)),this,SLOT(expand(bool)));
    connect(mAnimation,SIGNAL(valueChanged(QVariant)),this,SLOT(animChanged(QVariant)));
    //mContent->setVisible(false);

}

void TracksSettingsContainer::setWidget(QWidget *widget)
{
    mContentLayout->insertWidget(0,widget);
    mContent = widget;
    mContent->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    mAnimation->setStartValue(widget->height());
    mAnimation->setEndValue(0);
    mAnimation->setDuration(200);

    //widget->setStyleSheet("QWidget {background-color:lightgray}");
    //    setTitle(widget->windowTitle());
    //    setIcon(widget->windowIcon());
}

void TracksSettingsContainer::expand(bool expand)
{

    mAnimation->stop();
    mAnimation->setDirection(expand ? QAbstractAnimation::Backward : QAbstractAnimation::Forward);
    mAnimation->start();

}

void TracksSettingsContainer::collapse(bool collapse)
{
    //mContent->setVisible(collapse);
}

void TracksSettingsContainer::animChanged(const QVariant &value)
{
    mContent->setMaximumHeight(mAnimation->currentValue().toInt());

   // mContent->setMaximumHeight(mAnimation->currentValue().toInt());

}

}} // end namespace
