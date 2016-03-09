#include "settingsdialog.h"
#include "pathsettingswidget.h"
#include "genomsettingswidget.h"
#include <QDebug>
namespace big {
namespace gui {
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    mListWidget = new QListWidget;
    mTabWidget = new QTabWidget;
    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Reset|QDialogButtonBox::Apply|QDialogButtonBox::Cancel);

    mListWidget->setMaximumWidth(200);


    QHBoxLayout * cLayout = new QHBoxLayout;
    cLayout->addWidget(mListWidget);
    cLayout->addWidget(mTabWidget);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addLayout(cLayout);
    mainLayout->addWidget(mButtonBox);


    setLayout(mainLayout);


    addWidget(new PathSettingsWidget(),"data");
    addWidget(new GenomSettingsWidget(),"data");

    resize(800,400);

    connect(mListWidget,SIGNAL(currentRowChanged(int)),this,SLOT(updateTab(int)));
    connect(mButtonBox,SIGNAL(rejected()),this,SLOT(reject()));

    setWindowTitle(tr("Settings"));

}


void SettingsDialog::addWidget(AbstractSettingsWidget *widget,const QString& categorie)
{
    if (!mWidgets.keys().contains(categorie))
        mWidgets[categorie] = QList<AbstractSettingsWidget*>();


    mWidgets[categorie].append(widget);

    createList();

    //    mStacks->addWidget(widget);
    //    mListWidget->addItem(new QListWidgetItem(widget->windowIcon(),widget->windowTitle()));

}

bool SettingsDialog::save()
{
    QString categorie = mListWidget->currentItem()->text();
    bool status = true;

    foreach ( AbstractSettingsWidget * widget , mWidgets.value(categorie))
        status&=widget->save();

    return status;

}

bool SettingsDialog::load()
{

    QString categorie = mListWidget->currentItem()->text();
    bool status = true;

    foreach ( AbstractSettingsWidget * widget , mWidgets.value(categorie))
        status&=widget->load();

    return status;
}

void SettingsDialog::updateTab(int row)
{
    mTabWidget->clear();

    foreach ( AbstractSettingsWidget * widget , mWidgets.value(mListWidget->currentItem()->text()))
        mTabWidget->addTab(widget, widget->windowTitle());


}

void SettingsDialog::createList()
{
    mListWidget->clear();

    foreach (QString title, mWidgets.keys())
    {
        mListWidget->addItem(title);
    }


}

}}
