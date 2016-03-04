#include "tracklistwidget.h"
namespace big {
namespace gui {
TrackListWidget::TrackListWidget(QWidget *parent) : QWidget(parent)
{

    QSplitter * splitter = new QSplitter(Qt::Horizontal);

    mLeftFrame = new QFrame;
    mRightFrame = new QFrame;

    mLeftFrame->setStyleSheet("background-color:'darkgray'");

    mLeftFrame->setMaximumWidth(200);

    splitter->addWidget(mLeftFrame);
    splitter->addWidget(mRightFrame);

    QVBoxLayout * l = new QVBoxLayout;

    l->addWidget(splitter);

    l->setContentsMargins(0,0,0,0);

    setLayout(l);

}

}}
