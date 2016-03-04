#ifndef DATABASESETTINGSWIDGET_H
#define DATABASESETTINGSWIDGET_H
#include "abstractsettingswidget.h"
namespace big {
namespace gui {
class DatabaseSettingsWidget : public AbstractSettingsWidget
{
    Q_OBJECT
public:
    DatabaseSettingsWidget(QWidget * parent = 0);

public Q_SLOTS:
    bool save();
    bool load();


};

}} // namespace
#endif // DATABASESETTINGSWIDGET_H
