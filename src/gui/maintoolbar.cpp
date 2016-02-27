#include "maintoolbar.h"
#include <QSpacerItem>
namespace big {
MainToolBar::MainToolBar(QWidget * parent):
    QToolBar(parent)
{
    mGenomComboBox = new QComboBox();
    mChromosomComboBox = new QComboBox();
    mLocationEdit= new QLineEdit();

    mGenomComboBox->addItem("Hg19");
    mChromosomComboBox->addItem("chr1");

    QWidget * spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    addAction("test");

    addWidget(spacer);
    addWidget(mGenomComboBox);
    addWidget(mChromosomComboBox);
    addWidget(mLocationEdit);

    mGenomComboBox->setMinimumWidth(100);
    mLocationEdit->setMaximumWidth(400);

    mLocationEdit->setPlaceholderText("chr4:102344342-24234234234");


}
}
