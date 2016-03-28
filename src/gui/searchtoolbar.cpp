#include "searchtoolbar.h"
#include <QSpacerItem>
#include <QRegExpValidator>
#include "app.h"
namespace big {
namespace gui {
SearchToolBar::SearchToolBar(QWidget * parent):
    QToolBar(parent)
{
    mGenomComboBox     = new QComboBox();
    mChromosomComboBox = new QComboBox();
    mLocationEdit      = new QLineEdit();

    QWidget * spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    createActions();
    loadAvaibleGenom();

    addWidget(spacer);
    addWidget(mGenomComboBox);
    addWidget(mChromosomComboBox);
    addWidget(mLocationEdit);

    mGenomComboBox->setMinimumWidth(100);
    mLocationEdit->setMaximumWidth(300);
    mLocationEdit->setPlaceholderText("chr4:102344342-24234234234");




    connect(mLocationEdit,SIGNAL(returnPressed()),this,SLOT(locationEditChanged()));
    connect(mChromosomComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(chromosomChanged()));
    connect(mGenomComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(genomComboBoxChanged()));

}

void SearchToolBar::setGenom(Genom *genom)
{
    if (genom){
        mChromosomComboBox->clear();
        mChromosomComboBox->addItems(genom->chromosoms());
    }
}


void SearchToolBar::setSelection(const Selection &selection)
{
    Region region(selection.chromosom(),
                  selection.start(),
                  selection.end());

    mLocationEdit->setText(region.toString());
}

void SearchToolBar::loadAvaibleGenom()
{
    mGenomComboBox->clear();
    foreach ( QString name, App::i()->avaibleGenoms())
    {
        Genom genom(App::i()->genomPath(name));
        mGenomComboBox->addItem(genom.name(), name);

    }
}

void SearchToolBar::genomComboBoxChanged()
{
    emit genomChanged(mGenomComboBox->currentData().toString());
}

void SearchToolBar::createActions()
{
    //    QAction * showChromosomAction = addAction("show chrom");


}

void SearchToolBar::locationEditChanged()
{
    Selection region;
    region.setRegion(mLocationEdit->text());
    mChromosomComboBox->setCurrentText(region.chromosom());
    emit selectionChanged(region);
}

void SearchToolBar::chromosomChanged()
{
    emit selectionChanged(Selection(mChromosomComboBox->currentText(),0,0));
}
}}
