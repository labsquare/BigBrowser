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
namespace gui {

using namespace core;





class ChromosomWidget : public QWidget
{
    Q_OBJECT
public:
    ChromosomWidget(QWidget * parent = 0);
    ~ChromosomWidget();


    Genom * genom();
    void setGenom(Genom * genom);



public Q_SLOTS:
    void setSelection(const QString& chromosom, quint64 start, quint64 end);
    void setSelection(const Region& region);
    void setZoom(int factor);

Q_SIGNALS:
    void selectionChanged(const QString& chromosom, quint64 start, quint64 end);
    void selectionChanged(const Region& region);
protected Q_SLOTS:
    void updateChromosom();

protected:
    // ----------------------------------------------------------
    // Override Qt event handler
    // ----------------------------------------------------------
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent * event)Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event)Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event)Q_DECL_OVERRIDE;
    void enterEvent(QEvent * event)Q_DECL_OVERRIDE;
    void leaveEvent(QEvent * event)Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * event)Q_DECL_OVERRIDE;

    // ----------------------------------------------------------
    // Drawing
    // ----------------------------------------------------------
    void drawRegions(QPainter * painter);
    void drawLabels(QPainter *painter);
    void drawCursorLayer(QPainter *painter);
    void drawFrameLayer(QPainter *painter);

    QPainterPath getChromosomWrapperShape(int wrapperPadding, int wrc) const;

    // ----------------------------------------------------------
    // Helper
    // ----------------------------------------------------------
    inline quint64 pixelToBase(int pixel) {return (pixel-mOffsetX) / mP2BCoeff;}
    inline int baseToPixel(quint64 base) {return base * mP2BCoeff + mOffsetX;}
    Region getRegionAtPixel(int pixelPos);
    void initStainColorFromRegions();
    void updateFrame(QRect newFrame, bool updateSelector=true);



private:

    // ----------------------------------------------------------
    // Define sub class/enum
    // ----------------------------------------------------------
    //! Different cursor modes managed by the widget
    enum CursorMode
    {
        normal  = 0,
        cutter  = 1,
        select  = 2,
        move    = 3,
        resizeL = 4,
        resizeR = 5
    };


    // ----------------------------------------------------------
    // Business data
    // ----------------------------------------------------------
    //! The genom to display
    Genom * mGenom;

    //! The list of regions of the chromosom
    RegionList mChromosomRegions;

    //! The selected region of the genom
    Region mSelector;


    // ----------------------------------------------------------
    // Cursor management
    // ----------------------------------------------------------
    //! The current mode of the cursor
    CursorMode mCursorMode;

    //! The current position of the cursor in the widget referential (pixel)
    QPoint mCursorPosition;

    //! Is the cursor active (mouse over the widget)
    bool mCursorActive;

    //! The region selected (in select mode of course... not the active region -> see mSelector)
    Region mCursorRegion;

    //! The position of the cursor in the chromosome referential (base)
    quint64 mCursorBasePosition ;

    //! In select mode : the position of the cursor at the "mouse left button press"
    QPoint mCursorFirstPoint;


    // ----------------------------------------------------------
    // Frame management
    // ----------------------------------------------------------
    //! The active frame
    QRect mFrame;

    //! Used for feedback in Creation/Move or Resize mode
    QRect mFrameGhost;

    //! The left handle to resize the active frame to the left
    QRect mFrameHandleL;

    //! The right handle to resize the active frame to the right
    QRect mFrameHandleR;


    // ----------------------------------------------------------
    // Chromosome drawing
    // ----------------------------------------------------------
    //! Horizontal canvas inner margin
    float mOffsetX;

    //! Vertical canvas inner margin
    float mOffsetY;

    //! Height of the chromosom shape
    float mChromosomHeight;

    //! Width of the chromosom shape (canvas width - 2 * mOffsetX)
    float mChromosomWidth;

    //! Coeff to swith referential pixels <-> chr bases
    float mP2BCoeff;

    //! Bakground image : Keeping it in memory to avoid to redraw it too often
    QImage mBackgroundLayer;

    //! The mapping between chromosom region's stains and color
    QHash<QString, QColor> mStains;
};

}}

#endif // CHROMOSOMWIDGET_H
