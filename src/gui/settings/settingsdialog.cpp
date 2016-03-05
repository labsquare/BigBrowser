#include "settingsdialog.h"
#include "databasesettingswidget.h"

namespace big {
namespace gui {
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    mListWidget = new QListWidget;
    mStacks = new QStackedWidget;
    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Reset|QDialogButtonBox::Apply|QDialogButtonBox::Cancel);

    mListWidget->setMaximumWidth(200);


    QHBoxLayout * cLayout = new QHBoxLayout;
    cLayout->addWidget(mListWidget);
    cLayout->addWidget(mStacks);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addLayout(cLayout);
    mainLayout->addWidget(mButtonBox);


    setLayout(mainLayout);


    addWidget(new DatabaseSettingsWidget());

    resize(800,400);

    connect(mListWidget,SIGNAL(currentRowChanged(int)), mStacks,SLOT(setCurrentIndex(int)));
    connect(mButtonBox,SIGNAL(rejected()),this,SLOT(reject()));

    setWindowTitle(tr("Settings"));

}

void SettingsDialog::addWidget(AbstractSettingsWidget *widget)
{

    mStacks->addWidget(widget);
    mListWidget->addItem(new QListWidgetItem(widget->windowIcon(),widget->windowTitle()));
    mWidgets.append(widget);

}

bool SettingsDialog::save()
{

    foreach ( AbstractSettingsWidget * widget , mWidgets)
        widget->save();

    return false;

}

bool SettingsDialog::load()
{

    foreach ( AbstractSettingsWidget * widget , mWidgets)
        widget->load();

    return false;
}

}}
