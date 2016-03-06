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
    //    addWidget(mChromosomComboBox);
    addWidget(mLocationEdit);

    mGenomComboBox->setMinimumWidth(100);
    mLocationEdit->setMaximumWidth(400);

    mLocationEdit->setPlaceholderText("chr4:102344342-24234234234");

    mGenomComboBox->addItems(App::i()->avaibleGenoms());



}


//void MainToolBar::setGenom(Genom *genom)
//{
//    mGenom = genom;

//    mGenomComboBox->addItem(mGenom->name());
//    mChromosomComboBox->addItem("chr1");
//    mChromosomComboBox->addItem("chr2");
//    mChromosomComboBox->addItem("chr3");
//    mChromosomComboBox->addItem("chr4");
//    mChromosomComboBox->addItem("chr5");
//    mChromosomComboBox->addItem("chr6");
//    mChromosomComboBox->addItem("chr7");
//    mChromosomComboBox->addItem("chr8");
//    mChromosomComboBox->addItem("chr9");
//    mChromosomComboBox->addItem("chr10");
//    mChromosomComboBox->addItem("chr11");
//    mChromosomComboBox->addItem("chr12");
//    mChromosomComboBox->addItem("chr13");
//    mChromosomComboBox->addItem("chr14");
//    mChromosomComboBox->addItem("chr15");
//    mChromosomComboBox->addItem("chr16");
//    mChromosomComboBox->addItem("chr17");
//    mChromosomComboBox->addItem("chr18");
//    mChromosomComboBox->addItem("chr19");
//    mChromosomComboBox->addItem("chr20");
//    mChromosomComboBox->addItem("chr21");
//    mChromosomComboBox->addItem("chr22");
//    mChromosomComboBox->addItem("chrX");
//    mChromosomComboBox->addItem("chrY");



//}

//void MainToolBar::setSelector(Selector *selector)
//{
//    mSelector = selector;
//    connect(mSelector,SIGNAL(changed()),this,SLOT(updateLocation()));
//}

//void MainToolBar::locationChanged()
//{

//    mSelector->setSelection(mLocationEdit->text());



//}

//void MainToolBar::updateLocation()
//{
//    mLocationEdit->setText(mSelector->toString());
//}


void MainToolBar::createActions()
{
    QAction * showChromosomAction = addAction("show chrom");

}

void MainToolBar::loadChromosom()
{



}
}}
