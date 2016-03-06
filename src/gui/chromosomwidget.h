#ifndef CHROMOSOMWIDGET_H
#define CHROMOSOMWIDGET_H
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include "cytobandreader.h"
#include "region.h"
#include "genom.h"
#include "regionlist.h"
#include <QHash>

namespace big {
using namespace core;

namespace gui {
class ChromosomWidget : public QWidget
{

    Q_OBJECT
public:

    ChromosomWidget(QWidget * parent = 0);
    ~ChromosomWidget();


    Genom * genom();
    void setGenom(Genom * genom);

    Region *selector();


public Q_SLOTS:
    void setSelection(const QString& chromosom, quint64 start, quint64 end);

Q_SIGNALS:
    void selectionChanged(const QString& chromosom, quint64 start, quint64 end);

protected Q_SLOTS:
    void updateChromosom();

protected:
    // Override Qt event handler
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent * event)Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event)Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event)Q_DECL_OVERRIDE;
    void leaveEvent(QEvent * event)Q_DECL_OVERRIDE;
    void enterEvent(QEvent * event)Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * event)Q_DECL_OVERRIDE;

    // Drawing
    void drawRegions(QPainter * painter);
    void drawLabels(QPainter *painter);
    void drawFrameLayer(QPainter *painter);
    QPainterPath getChromosomWrapperShape(int wrapperPadding, int wrc) const;

    // Helper
    inline quint64 pixelToBase(int pixel) {return (pixel-mOffsetX) / mB2PCoeff;}
    inline int baseToPixel(quint64 base) {return base * mB2PCoeff + mOffsetX;}
    Region getRegionAtPixel(int pixelPos);

private:
    Genom * mGenom;
    Region * mSelector;

    QString mCytoBandFileName;
    RegionList mRegionList;
    RegionList mChromosoms;
    QHash<QString, QColor> mStains;

    // Cursor management
    QPoint mCursorPosition;
    bool mCursorActive;
    bool mCursorClicked ;
    quint64 mCursorBasePosition ;
    Region mCursorRegion;

    // Frame management
    QRect mFrame;
    QRect mFrameGhost;
    QPoint mFrameFirstPoint;
    QRect mFrameHandleL;
    QRect mFrameHandleM;
    QRect mFrameHandleR;



    // Define chromosome offset (canvas inner margin)
    float mOffsetX;
    float mOffsetY;
    float mChromosomHeight;
    float mChromosomWidth;
    float mB2PCoeff;

    // Keeping background in memory to avoid to redraw it too often
    QImage mBackgroundLayer;
};

}}

#endif // CHROMOSOMWIDGET_H
