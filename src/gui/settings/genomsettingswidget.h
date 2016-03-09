#ifndef GENOMSETTINGSWIDGET_H
#define GENOMSETTINGSWIDGET_H
#include "abstractsettingswidget.h"

namespace big {
namespace gui {

class GenomSettingsWidget : public AbstractSettingsWidget
{
public:
    GenomSettingsWidget(QWidget * parent = 0);

   public Q_SLOTS:
    bool save();
    bool load();

};


}}


#endif // GENOMSETTINGSWIDGET_H
