#ifndef CHROMOSOMWIDGET_H
#define CHROMOSOMWIDGET_H
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include "cytobandreader.h"
#include "region.h"
#include "regionlist.h"
#include "section.h"
#include <QHash>

namespace big {
using namespace core;

namespace gui {
class ChromosomWidget : public QWidget
{

    Q_OBJECT
public:

    ChromosomWidget(const QString& filename, QWidget * parent = 0);
    Section * selection;



public Q_SLOTS:
    void setChromosom(const QString& chromosom);
    void setRange(qint64 start, qint64 end);





protected:
    // Override Qt event handler
    void paintEvent(QPaintEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void leaveEvent(QEvent * event);
    void enterEvent(QEvent * event);
    void keyPressEvent(QKeyEvent * event);

    // Drawing
    void drawRegions(QPainter * painter);
    void drawLabels(QPainter *painter);
    void drawFrameLayer(QPainter *painter);
    QPainterPath getChromosomWrapperShape(int wrapperPadding, int wrc) const;

    // Helper
    inline qint64 pixelToBase(int pixel) {return (pixel-mOffsetX) / mB2PCoeff;}
    inline int baseToPixel(qint64 base) {return base * mB2PCoeff + mOffsetX;}
    Region getRegionAtPixel(int pixelPos);



private:
    QString mCytoBandFileName;
    RegionList mRegionList;
    QList <Region> mChromosoms;
    QHash<QString, QColor> mStains;
    Region mRegionSelector;

    // Cursor management
    QPoint mCursorPosition;
    bool mCursorActive = false;
    bool mCursorClicked = false;
    qint64 mCursorBasePosition = 0;
    Region mCursorRegion;

    // Frame management
    QRect mFrame;
    QRect mFrameGhost;
    QPoint mFrameFirstPoint;



    // Define chromosome offset (canvas inner margin)
    float mOffsetX = 30;
    float mOffsetY = 30;
    float mChromosomHeight = 30;
    float mChromosomWidth = 0;
    float mB2PCoeff = 0;

    // Keeping background in memory to avoid to redraw it too often
    QImage mBackgroundLayer;
};

}}

#endif // CHROMOSOMWIDGET_H
