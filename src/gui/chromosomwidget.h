#ifndef CHROMOSOMWIDGET_H
#define CHROMOSOMWIDGET_H
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include "cytobandreader.h"
#include "region.h"
#include "regionlist.h"
#include <QHash>

namespace big {
using namespace core;

namespace gui {
class ChromosomWidget : public QWidget
{

    Q_OBJECT
public:

    ChromosomWidget(const QString& filename, QWidget * parent = 0);

public Q_SLOTS:
    void setChromosom(const QString& chromosom);
    void setRange(qint64 start, qint64 end);






protected:
    void paintEvent(QPaintEvent*);

    void drawChromosom(QPainter * painter);
    void drawChromosomWrapper(QPainter * painter);



private:
    QString mCytoBandFileName;
    RegionList mRegionList;
    QList <Region> mChromosoms;
    QHash<QString, QColor> mStains;

    Region mRegionSelector;




};

}}

#endif // CHROMOSOMWIDGET_H
