#include "selecttoolbar.h"
#include <QSpacerItem>
#include <QRegExpValidator>
#include "app.h"
namespace big {
namespace gui {
SelectToolBar::SelectToolBar(QWidget * parent):
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

void SelectToolBar::setGenom(Genom *genom)
{
    if (genom){
        mChromosomComboBox->clear();
        mChromosomComboBox->addItems(genom->chromosoms());
    }
}

void SelectToolBar::reset()
{
    loadAvaibleGenom();
    mLocationEdit->clear();
}

void SelectToolBar::setSelection(const Region &region)
{
    mLocationEdit->setText(region.toString());
}

void SelectToolBar::loadAvaibleGenom()
{
    mGenomComboBox->clear();
    foreach ( QString name, App::i()->avaibleGenoms())
    {
        Genom genom(App::i()->genomPath(name));
        mGenomComboBox->addItem(genom.name(), name);

    }
}

void SelectToolBar::genomComboBoxChanged()
{
    emit genomChanged(mGenomComboBox->currentData().toString());
}

void SelectToolBar::createActions()
{
    //    QAction * showChromosomAction = addAction("show chrom");


}

void SelectToolBar::locationEditChanged()
{
    Region region(mLocationEdit->text());
    mChromosomComboBox->setCurrentText(region.chromosom());
    emit selectionChanged(region);
}

void SelectToolBar::chromosomChanged()
{
    mLocationEdit->clear();
    emit selectionChanged(Region(mChromosomComboBox->currentText(),0,0));
}
}}
