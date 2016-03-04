#include "databasesettingswidget.h"

namespace big {
namespace gui {
DatabaseSettingsWidget::DatabaseSettingsWidget(QWidget * parent)
    :AbstractSettingsWidget(parent)
{

    setWindowTitle("Database");

    QPixmap pix(64,64);
    pix.fill(Qt::red);

    setWindowIcon(QIcon(pix));


    addTab(new QWidget,"settings");




}

bool DatabaseSettingsWidget::save()
{

    return true;
}

bool DatabaseSettingsWidget::load()
{

    return true;
}

}} // end namespace
