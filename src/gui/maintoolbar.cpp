#include "maintoolbar.h"
#include <QSpacerItem>

MainToolBar::MainToolBar(QWidget * parent):
    QToolBar(parent)
{
    mGenomComboBox = new QComboBox();
    mLocationEdit= new QLineEdit();

    mGenomComboBox->addItem("Hg19");

    QWidget * spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    addAction("test");

    addWidget(spacer);
    addWidget(mGenomComboBox);
    addWidget(mLocationEdit);

    mGenomComboBox->setMinimumWidth(100);
    mLocationEdit->setMaximumWidth(400);

    mLocationEdit->setPlaceholderText("chr4:102344342-24234234234");


}
