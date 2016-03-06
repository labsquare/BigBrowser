#include "maintoolbar.h"
#include <QSpacerItem>
#include <QRegExpValidator>
#include "app.h"
namespace big {
namespace gui {
MainToolBar::MainToolBar(QWidget * parent):
    QToolBar(parent)
{
    mGenomComboBox     = new QComboBox();
    mChromosomComboBox = new QComboBox();
    mLocationEdit      = new QLineEdit();

    QWidget * spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    addWidget(spacer);
    addWidget(mGenomComboBox);
    addWidget(mChromosomComboBox);
    addWidget(mLocationEdit);

    mGenomComboBox->setMinimumWidth(100);
    mLocationEdit->setMaximumWidth(400);
    mLocationEdit->setPlaceholderText("chr4:102344342-24234234234");
    mGenomComboBox->addItems(App::i()->avaibleGenoms());

    connect(mLocationEdit,SIGNAL(returnPressed()),this,SLOT(locationEditChanged()));
    connect(mChromosomComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(chromosomChanged()));

}

void MainToolBar::setGenom(Genom *genom)
{
    if (genom){
        mChromosomComboBox->clear();
        mChromosomComboBox->addItems(genom->chromosoms());
    }
}

void MainToolBar::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    Region region(chromosom,start, end);
    mLocationEdit->setText(region.toString());
}

void MainToolBar::createActions()
{
    QAction * showChromosomAction = addAction("show chrom");

}

void MainToolBar::locationEditChanged()
{
    Region region(mLocationEdit->text());
    emit selectionChanged(region.chromosom(),region.start(),region.end());
}

void MainToolBar::chromosomChanged()
{
    emit selectionChanged(mChromosomComboBox->currentText(),0,0);
}
}}
