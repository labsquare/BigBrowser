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


    addWidget(spacer);
    addWidget(mGenomComboBox);
    addWidget(mChromosomComboBox);
    addWidget(mLocationEdit);

    mGenomComboBox->setMinimumWidth(100);
    mLocationEdit->setMaximumWidth(300);
    mLocationEdit->setPlaceholderText("chr4:102344342-24234234234");
    mGenomComboBox->addItems(App::i()->avaibleGenoms());

    connect(mLocationEdit,SIGNAL(returnPressed()),this,SLOT(locationEditChanged()));
    connect(mChromosomComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(chromosomChanged()));


}

void SearchToolBar::setGenom(Genom *genom)
{
    if (genom){
        mChromosomComboBox->clear();
        mChromosomComboBox->addItems(genom->chromosoms());
    }
}

void SearchToolBar::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    Region region(chromosom,start, end);
    mLocationEdit->setText(region.toString());
}



void SearchToolBar::createActions()
{
//    QAction * showChromosomAction = addAction("show chrom");


}

void SearchToolBar::locationEditChanged()
{
    Region region(mLocationEdit->text());
    mChromosomComboBox->setCurrentText(region.chromosom());
    emit selectionChanged(region.chromosom(),region.start(),region.end());
}

void SearchToolBar::chromosomChanged()
{
    emit selectionChanged(mChromosomComboBox->currentText(),0,0);
}
}}
