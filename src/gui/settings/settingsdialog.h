#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QList>
#include <QStackedWidget>
#include <QListWidget>
#include <QDialogButtonBox>
#include "abstractsettingswidget.h"
namespace big {
namespace gui {
class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);

public Q_SLOTS:
    bool save();
    bool load();

protected:
    void addWidget(AbstractSettingsWidget * widget);


private:
    QList<AbstractSettingsWidget*> mWidgets;

    QListWidget * mListWidget;
    QStackedWidget * mStacks;
    QDialogButtonBox * mButtonBox;

};

}}
#endif // SETTINGSWIDGET_H
