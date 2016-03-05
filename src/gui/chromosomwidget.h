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

    void drawRegions(QPainter * painter);
    void drawLabels(QPainter *painter);
    QPainterPath getChromosomWrapperShape(int wrapperPadding, int wrc) const;



private:
    QString mCytoBandFileName;
    RegionList mRegionList;
    QList <Region> mChromosoms;
    QHash<QString, QColor> mStains;

    Region mRegionSelector;


    // Define chromosome offset (canvas inner margin)
    const float mOffsetX = 30;
    const float mOffsetY = 30;
    const float mChromosomHeight = 30;


};

}}

#endif // CHROMOSOMWIDGET_H
