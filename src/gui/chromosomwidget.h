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

public:

    ChromosomWidget(QWidget * parent = 0);


public Q_SLOTS:
void loadCytoBand(const QString& filename);

protected:
    void paintEvent(QPaintEvent*);

    void drawChromosom(QPainter * painter);



private:
    RegionList mRegionList;
    QHash<QString, QList<Region> > mChromosoms;
    QHash<QString, QColor> mStains;


};

}}

#endif // CHROMOSOMWIDGET_H
