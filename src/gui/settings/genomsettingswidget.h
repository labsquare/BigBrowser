#ifndef GENOMSETTINGSWIDGET_H
#define GENOMSETTINGSWIDGET_H
#include <QtWidgets>
#include <QDir>
#include <QFileInfo>
#include <QtCore>
#include <QTextStream>
#include "quazip.h"
#include "quazipfile.h"
#include "abstractsettingswidget.h"
#include "genommodel.h"
namespace big {
namespace gui {

class GenomSettingsWidget : public AbstractSettingsWidget
{
    Q_OBJECT
public:
    GenomSettingsWidget(QWidget * parent = 0);

   public Q_SLOTS:
    bool save();
    bool load();

protected Q_SLOTS:
    void loadGenomList();
    void removeFile();
    void addLocalFile();
    void addRemoteFile();

private:
QTableView * mView;
GenomModel * mModel;



};


}}


#endif // GENOMSETTINGSWIDGET_H
