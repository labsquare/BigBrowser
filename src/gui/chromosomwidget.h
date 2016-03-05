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

/*!
 * \brief ChromosomWidget is a widget dedicated to the navigation and the selection of a region in a provided chromosome. It's like a minimap for the application.
 */
class ChromosomWidget : public QWidget
{

    Q_OBJECT
public:

    /*!
     * \brief Default constructor
     */
    ChromosomWidget(const QString& filename, QWidget * parent = 0);

public Q_SLOTS:

    void setChromosom(const QString& chromosom);

    void setRange(qint64 start, qint64 end);






protected:
    // Override Qt event handler
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void leaveEvent(QEvent * event);
    void enterEvent(QEvent * event);

    // Drawing
    void drawRegions(QPainter * painter);
    void drawLabels(QPainter *painter);
    void drawFrameLayer(QPainter *painter);

    // Helper
    QPainterPath getChromosomWrapperShape(int wrapperPadding, int wrc) const;


private:
    QString mCytoBandFileName;
    RegionList mRegionList;
    QList <Region> mChromosoms;
    QHash<QString, QColor> mStains;

    Region mRegionSelector;


    QPoint mCursorPosition;
    bool mCursorActive = false;
    bool mCursorClicked = false;
    qint64 mCursorBasePosition = 0;
    Region mCursorRegion;


    // Define chromosome offset (canvas inner margin)
    const float mOffsetX = 30;
    const float mOffsetY = 30;
    const float mChromosomHeight = 30;

    // Keeping background in memory to avoid to redraw it too often
    QImage mBackgroundLayer;

};

}}

#endif // CHROMOSOMWIDGET_H
