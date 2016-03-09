#include "genomsettingswidget.h"
#include <QtWidgets>
namespace big {
namespace gui {
GenomSettingsWidget::GenomSettingsWidget(QWidget * parent)
    :AbstractSettingsWidget(parent)
{
    setWindowTitle("genom");

    QVBoxLayout * l = new QVBoxLayout;
    l->addWidget(new QPushButton("genom"));
    setLayout(l);


}

bool GenomSettingsWidget::save()
{
    return false;
}

bool GenomSettingsWidget::load()
{
    return false;
}

}}
