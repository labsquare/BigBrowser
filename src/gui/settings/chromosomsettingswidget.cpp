#include "chromosomsettingswidget.h"
namespace big {
namespace gui {
ChromosomSettingsWidget::ChromosomSettingsWidget(QWidget * parent)
    :AbstractSettingsWidget(parent)
{

    QVBoxLayout * layout = new QVBoxLayout;

    layout->addWidget(new QPushButton("salut"));

    setLayout(layout);

    setWindowTitle(tr("Chromosom"));


}

bool ChromosomSettingsWidget::save()
{
    return true;
}

bool ChromosomSettingsWidget::load()
{


    return true;
}

}} // end namespace
