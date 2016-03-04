#ifndef ABSTRACTSETTINGSWIDGET_H
#define ABSTRACTSETTINGSWIDGET_H

#include <QWidget>
#include <QTabWidget>
namespace big {
namespace gui {
class AbstractSettingsWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit AbstractSettingsWidget(QWidget *parent = 0);

public Q_SLOTS:
    virtual bool save() = 0;
    virtual bool load() = 0;


};


}}
#endif // ABSTRACTSETTINGSWIDGET_H
