#ifndef DATABASESETTINGSWIDGET_H
#define DATABASESETTINGSWIDGET_H
#include <QtWidgets>
#include "abstractsettingswidget.h"
namespace big {
namespace gui {
class PathSettingsWidget : public AbstractSettingsWidget
{
    Q_OBJECT
public:
    PathSettingsWidget(QWidget * parent = 0);

public Q_SLOTS:
    bool save();
    bool load();

protected slots:
    void openFileBrowser();

private:
    QLineEdit * mGenomPath;
    QLineEdit * mAnnotationPath;


};

}} // namespace
#endif // DATABASESETTINGSWIDGET_H
