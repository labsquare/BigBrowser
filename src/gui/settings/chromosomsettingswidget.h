#ifndef DISPLAYSETTINGSWIDGET_H
#define DISPLAYSETTINGSWIDGET_H
#include "abstractsettingswidget.h"
#include <QtWidgets>

namespace big {
namespace gui {

class ChromosomSettingsWidget : public AbstractSettingsWidget
{
public:
    ChromosomSettingsWidget(QWidget * parent = 0);

    bool save();
    bool load();



};

}}
#endif // DISPLAYSETTINGSWIDGET_H
