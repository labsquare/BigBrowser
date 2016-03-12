#include "chromosomwidget.h"
#include "app.h"
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QStyle>
namespace big {
namespace gui {



ChromosomWidget::ChromosomWidget( QWidget * parent)
    :QWidget(parent), mGenom(0)
{
    // Define chromosome offset (canvas inner margin)
    mOffsetX         = 30;
    mOffsetY         = 30;
    mChromosomHeight = 30;
    mChromosomWidth  = 0;
    mB2PCoeff        = 0;

    // Create an empty selector
    mSelector = new Region();

    // Cursor management
    mCursorActive       = false;
    mCursorMode         = cutter;
    mCursorBasePosition = 0;


    setMouseTracking(true);

}

ChromosomWidget::~ChromosomWidget()
{
    // Do not delete genom
    delete mSelector;
}

Genom *ChromosomWidget::genom()
{
    return mGenom;
}

void ChromosomWidget::setGenom(Genom *genom)
{
    mGenom = genom;
    if (mGenom)
    {
        // When genom changed, load new set of chromosom and show the first one
        if (mGenom->chromosomCount() > 0)
        {
            selector()->setChromosom(mGenom->chromosoms().first());
        }
        updateChromosom();
    }
}

Region * ChromosomWidget::selector()
{
    return mSelector;
}

void ChromosomWidget::updateChromosom()
{
    if (genom())
    {
        mChromosomRegions = genom()->chromosomBand(selector()->chromosom());
        initStainColorFromRegions();
        // Force the redraw of the background
        mBackgroundLayer = QImage();
        update();
    }
}

void ChromosomWidget::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    selector()->setRegion(chromosom,start,end);
    updateChromosom();
}

void ChromosomWidget::setZoom(int factor)
{

   quint64 middle = selector()->middle();

   selector()->setStart(middle - factor/2 );
   selector()->setEnd(middle + factor/2 );

   updateChromosom();

}








void ChromosomWidget::paintEvent(QPaintEvent *)
{
    // Is there something to draw ?
    if (mChromosomRegions.isEmpty())
    {
        QPainter painter(this);
        painter.setBrush(Qt::white);
        painter.setPen(Qt::transparent);
        painter.drawRect(rect());
        painter.setPen(Qt::black);
        painter.drawText(rect(),"404 not found", QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
        drawFrameLayer(&painter);
        return;
    }


    // When resize, need to (re)compute the background
    if (mBackgroundLayer.isNull() || mBackgroundLayer.rect() != rect())
    {
        // Recompute main drawing variables
        mChromosomWidth = rect().width() - mOffsetX * 2;
        mB2PCoeff = mChromosomWidth / mChromosomRegions.last().end();


        // 1st part : the wrapper
        QImage img1(size(), QImage::Format_ARGB32_Premultiplied);
        QPainter img1Painter;
        img1.fill(0);
        img1Painter.begin(&img1);
        img1Painter.setRenderHint(QPainter::Antialiasing);
        img1Painter.setBrush(QColor(250,250,250));
        img1Painter.setPen(QColor(100,100,100));
        img1Painter.drawPath(getChromosomWrapperShape(2, 5));
        // Todo : apply dropshadow to this image ?
        img1Painter.end();

        // 2nd part : the regions
        QImage img2(size(), QImage::Format_ARGB32_Premultiplied);
        QPainter img2Painter;
        img2.fill(0);
        img2Painter.begin(&img2);
        img2Painter.setRenderHint(QPainter::Antialiasing);
        img2Painter.setClipPath(getChromosomWrapperShape(1, 5));
        drawRegions(&img2Painter);
        img2Painter.end();

        // 3rd part : the labels
        QImage img3(size(), QImage::Format_ARGB32_Premultiplied);
        QPainter img3Painter;
        img3.fill(0);
        img3Painter.begin(&img3);
        drawLabels(&img3Painter);
        img3Painter.end();


        // Now merge the parts into background img
        mBackgroundLayer = QImage(size(), QImage::Format_ARGB32_Premultiplied);

        QPainter bgPainter(&mBackgroundLayer);
        bgPainter.setBrush(Qt::white);
        bgPainter.setPen(Qt::NoPen);
        bgPainter.drawRect(rect());

        bgPainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        bgPainter.drawImage(rect(), img1);
        bgPainter.drawImage(rect(), img2);
        bgPainter.drawImage(rect(), img3);
        bgPainter.end();

        // Recompute Frame is exists
        if (selector()->start() < selector()->end())
        {
            updateFrame(QRect(baseToPixel(selector()->start()),
                              0,
                              baseToPixel(selector()->end()) - baseToPixel(selector()->start()),
                              rect().height()-1),
                        false);
        }
    }

    // Display on screen
    QPainter painter(this);
    painter.drawImage(rect(), mBackgroundLayer);
    drawFrameLayer(&painter);
    if (mCursorActive)
    {
        drawCursorLayer(&painter);
    }
}


void ChromosomWidget::drawRegions(QPainter *painter)
{
    // Loop to draw regions
    foreach ( Region region, mChromosomRegions)
    {
        float regionWidth = region.length() * mB2PCoeff;
        float regionStart = mOffsetX + region.start() * mB2PCoeff;

        // Define region
        QRect fragment;
        fragment.setTopLeft(QPoint(regionStart, mOffsetY));
        fragment.setWidth(regionWidth + 1); // +1 to offset rounded performed by cast : float->int
        fragment.setHeight(mChromosomHeight);

        // Define brush accoding to thge region stain
        QColor base = mStains.value(region.data("stain").toString(),Qt::red);
        QLinearGradient lgrad(fragment.topLeft(), fragment.bottomLeft());
        lgrad.setColorAt(0.0, base.lighter(200));
        lgrad.setColorAt(0.4, base);
        lgrad.setColorAt(0.8, base);
        lgrad.setColorAt(1.0, base.darker(150));

        // Draw the region
        painter->setBrush(lgrad);
        painter->setPen(QPen(Qt::NoPen));
        painter->drawRect(fragment);
    }
}


void ChromosomWidget::drawLabels(QPainter *painter)
{
    // Define canvas boudaries
    int offsetY = mOffsetY + mChromosomHeight - 1 ;

    painter->setPen(QPen(QColor(50,50,50)));
    painter->setFont(QFont("Arial", 7));

    // Loop to draw labels
    foreach ( Region region, mChromosomRegions)
    {
        float regionWidth = region.length() * mB2PCoeff;
        float regionStart = mOffsetX + region.start() * mB2PCoeff;


        // Draw bounds lines
        if (region.data("stain").toString() != "acen")
            painter->drawLine(regionStart, mOffsetY, regionStart, offsetY );


        // Draw region label
        int deltaX =  regionWidth / 2 - 4 ;

        painter->save();
        painter->setPen(QPen(QColor(100,100,100)));
        painter->setTransform(QTransform());
        painter->translate(regionStart + deltaX, offsetY + 10);
        painter->rotate(90);
        painter->drawText(0,0, region.name());
        painter->restore();

    }
    // And the last line
    painter->drawLine(mOffsetX + mChromosomWidth, mOffsetY, mOffsetX + mChromosomWidth, offsetY );
}


void ChromosomWidget::drawFrameLayer(QPainter *painter)
{
    // Define colors
    QColor baseColor = qApp->style()->standardPalette().highlight().color();

    // Draw active frame if exist
    if (!mFrame.isNull())
    {
        QColor fg = baseColor;
        QColor bg = baseColor.lighter(150);
        bg.setAlpha(100);

        // Set alpha of the whole frame if not in normal mode
        if (mCursorMode != normal)
        {
            fg.setAlpha(75);
            bg.setAlpha(50);
        }

        painter->setPen(QPen(fg, 1, Qt::SolidLine));
        painter->setBrush(bg);
        painter->drawRect(mFrame);

        // Draw handle
        if (mFrame.contains(mCursorPosition) && mCursorMode == normal)
        {
            painter->setPen(QPen(fg, 3, Qt::SolidLine));
            painter->drawLine(mFrame.topLeft(), mFrame.bottomLeft());
            painter->drawLine(mFrame.topRight(), mFrame.bottomRight());
        }
    }

    // Draw the ghost when in move or resize mode
    if (!mFrameGhost.isNull() && (mCursorMode == move || mCursorMode == resizeL || mCursorMode == resizeR))
    {
        QColor bg = baseColor.lighter(150);
        bg.setAlpha(150);
        painter->setPen(QPen(baseColor, 1, Qt::SolidLine));
        painter->setBrush(bg);
        painter->drawRect(mFrameGhost);

        // Draw additional data if enough space
        int width = 200;
        int height = 15;
        if(rect().width() > width * 2)
        {
            int startX = (mFrameGhost.x() + mFrameGhost.width() / 2) - (width / 2);
            if (startX < 0)
            {
                startX = 0;
            }
            else if (startX + width > rect().width())
            {
                startX = rect().width() - width;
            }

            // Retrieve area information
            quint64 start = pixelToBase(mFrameGhost.left());
            quint64 end = pixelToBase(mFrameGhost.right());

            // Define label
            const QLocale & cLocale = QLocale::c();
            QString ss = cLocale.toString(start);
            ss.replace(cLocale.groupSeparator(), ' ');
            QString es = cLocale.toString(end);
            es.replace(cLocale.groupSeparator(), ' ');
            QString label = ss + "    -    " + es;
            QRect labelRect(startX, rect().height() - height, width -1, height -1);

            // Draw label
            bg = baseColor.lighter(200);
            painter->setBrush(bg);
            painter->setPen(QPen(baseColor, 1, Qt::SolidLine));
            painter->drawRect(labelRect);
            painter->drawText(labelRect,label, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
        }
    }
}


void ChromosomWidget::drawCursorLayer(QPainter *painter)
{
    // Define colors
    QColor baseColor = qApp->style()->standardPalette().highlight().color();

    if (mCursorMode == cutter || mCursorMode == select)
    {
        // Draw selection
        if (mCursorMode == select)
        {
            QBrush bg = baseColor.lighter(150);
            bg.setStyle(Qt::Dense6Pattern);
            painter->setPen(Qt::NoPen);
            painter->setBrush(bg);
            painter->drawRect(mFrameGhost);
            painter->setPen(baseColor.lighter(100));
            painter->drawLine(mCursorFirstPoint.x() , 0, mCursorFirstPoint.x(), rect().height());
        }

        // Draw the cursor
        painter->setPen(QPen(baseColor, 1, Qt::DashLine));
        painter->drawLine(mCursorPosition.x() , 0, mCursorPosition.x(), rect().height());
        setCursor(Qt::BlankCursor);

        // Draw additional data if enough space
        int width = 200;
        int height = 15;
        if(rect().width() > width * 2)
        {
            painter->setPen(QPen(baseColor, 1, Qt::SolidLine));
            painter->setBrush(baseColor.lighter(170));

            int startX = mCursorPosition.x() - (width / 2);
            if (startX < 0)
            {
                startX = 0;
            }
            else if (startX + width > rect().width())
            {
                startX = rect().width() - width;
            }

            QRect labelRect(startX, rect().height() - height, width -1, height -1);
            painter->drawRect(labelRect);

            const QLocale & cLocale = QLocale::c();
            QString ss = cLocale.toString(mCursorBasePosition);
            ss.replace(cLocale.groupSeparator(), ' ');

            QString label = mCursorRegion.chromosom().toUpper() + "    " + mCursorRegion.name() + "    " + ss;
            painter->drawText(labelRect,label, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
        }
    }

    switch(mCursorMode)
    {
        case CursorMode::resizeL:
        case CursorMode::resizeR:
            setCursor(Qt::SizeHorCursor);
            break;
        case CursorMode::move:
            setCursor(Qt::SizeAllCursor);
            break;
        case CursorMode::select:
        case CursorMode::cutter:
            setCursor(Qt::BlankCursor);
            break;

        default:
            if (mFrameHandleL.contains(mCursorPosition) || mFrameHandleR.contains(mCursorPosition))
            {
                setCursor(Qt::SizeHorCursor);
            }
            else if (mFrame.contains(mCursorPosition))
            {
                setCursor(Qt::SizeAllCursor);
            }
            else
            {
                setCursor(Qt::ArrowCursor);
            }
            break;
    }

}








//int wrapperPadding = 2;
//int wrc = 5; // wrapperRoundCoeff : pixel distance used by spline anchores
QPainterPath ChromosomWidget::getChromosomWrapperShape(int wrapperPadding, int wrc) const
{
    // Chromosom wrapper parameters
    float endPart1 = 0;
    float startPart2 = 0;
    float centX = 0;

    // Compute centromere special coordinates
    foreach ( Region region, mChromosomRegions)
    {
        QString stain = region.data("stain").toString();

        if(stain == "acen" && endPart1 == 0)
        {
            endPart1 = region.start() * mB2PCoeff;
            centX = region.end() * mB2PCoeff;
        }
        else if (endPart1 > 0  && stain != "acen" && startPart2 == 0)
        {
            startPart2 = region.start() * mB2PCoeff;
        }
    }

    // Defining key points of the spline line that will be used to draw the chromosome smoothly
    // A-----------B      D---------E
    // |             >CH<           |
    // J-----------I      G---------F
    float offsetX = mOffsetX - wrapperPadding;
    float offsetY = mOffsetY - wrapperPadding;
    QPoint A(offsetX, offsetY);
    QPoint B(offsetX + endPart1 + 2* wrapperPadding, offsetY);
    QPoint C(offsetX + centX, offsetY + mChromosomHeight / 2 - 5 );
    QPoint D(offsetX + startPart2, offsetY);
    QPoint E(offsetX + mChromosomWidth + 2* wrapperPadding , offsetY);

    offsetY += 2 * wrapperPadding + mChromosomHeight;
    QPoint F(offsetX + mChromosomWidth + 2* wrapperPadding, offsetY);
    QPoint G(offsetX + startPart2, offsetY);
    QPoint H(offsetX + centX, offsetY - mChromosomHeight / 2 + 5);
    QPoint I(offsetX + endPart1 + 2* wrapperPadding, offsetY);
    QPoint J(offsetX, offsetY );


    // Drawing chromosom wrapper
    QPainterPath path;


    // Drawing shape with centromere
    if (mStains.contains("acen"))
    {
        path.moveTo(A);
        path.cubicTo(QPoint(A.x() + wrc, A.y()),QPoint(B.x() - wrc, B.y()),B);
        path.cubicTo(QPoint(B.x() + wrc, B.y()),QPoint(C.x() - wrc, C.y()),C);
        path.cubicTo(QPoint(C.x() + wrc, C.y()),QPoint(D.x() - wrc, D.y()),D);
        path.cubicTo(QPoint(D.x() + wrc, D.y()),QPoint(E.x() - wrc, E.y()),E);
        path.cubicTo(QPoint(E.x() + wrc, E.y()),QPoint(F.x() + wrc, F.y()),F);
        path.cubicTo(QPoint(F.x() - wrc, F.y()),QPoint(G.x() + wrc, G.y()),G);
        path.cubicTo(QPoint(G.x() - wrc, G.y()),QPoint(H.x() + wrc, H.y()),H);
        path.cubicTo(QPoint(H.x() - wrc, H.y()),QPoint(I.x() + wrc, I.y()),I);
        path.cubicTo(QPoint(I.x() - wrc, I.y()),QPoint(J.x() + wrc, J.y()),J);
        path.cubicTo(QPoint(J.x() - wrc, J.y()),QPoint(A.x() - wrc, A.y()),A);
    }
    else
    {
        // else without centromere
        path.moveTo(A);
        path.cubicTo(QPoint(A.x() + wrc, A.y()),QPoint(E.x() - wrc, E.y()),E);
        path.cubicTo(QPoint(E.x() + wrc, E.y()),QPoint(F.x() + wrc, F.y()),F);
        path.cubicTo(QPoint(F.x() - wrc, F.y()),QPoint(J.x() + wrc, J.y()),J);
        path.cubicTo(QPoint(J.x() - wrc, J.y()),QPoint(A.x() - wrc, A.y()),A);
    }

    // Job done
    return path;
}

Region ChromosomWidget::getRegionAtPixel(int pixelPos)
{
    // Retrieve position in the genom
    Region region;
    float regionWidth, regionStart;

    // 1) Find the region (be human friendly with first and last regions)
    foreach (region, mChromosomRegions)
    {
        regionWidth = region.length() * mB2PCoeff;
        regionStart = mOffsetX + region.start() * mB2PCoeff;

        if (pixelPos < regionStart + regionWidth)
        {
            break;
        }
    }

    return region;
}

void ChromosomWidget::initStainColorFromRegions()
{
    mStains.clear();
    QColor base = QColor(200,200,200);

    mStains["stalk"]   = Qt::darkCyan;
    mStains["gvar"]    = QColor(144, 195, 212);
    mStains["gneg"]    = QColor(230,230,230);

    // Compute gradiant color for "gposXXX" region
    foreach ( Region region, mChromosomRegions)
    {
        QString stain = region.data("stain").toString();

        // We add "acen" stain only if exists in the chromom (allow us to detect next if need to draw it or not)
        if (stain == "acen" && !mStains.contains(stain))
        {
            mStains["acen"]    = QColor(80, 144, 212);
        }

        if (stain.startsWith("gpos") && !mStains.contains(stain))
        {
            QString stainLabel = stain;
            stain.remove(0,4);
            float value = 50 + (stain.toFloat() / 100.0) * 200.0; // 50 + % * 200     => max 250, min 50
            mStains[stainLabel] = base.darker(value);
        }
    }
}

void ChromosomWidget::updateFrame(QRect newFrame, bool updateSelector)
{
    mFrame = newFrame;
    mFrameHandleL = QRect(mFrame.left()-2, mFrame.top(), 4, rect().height());
    mFrameHandleR = QRect(mFrame.right()-2, mFrame.top(), 4, rect().height());

    // update section property
    if (updateSelector)
    {
        selector()->setStart(pixelToBase(mFrame.x()));
        selector()->setEnd(pixelToBase(mFrame.x()+mFrame.width()));
    }
    emit selectionChanged(selector()->chromosom(),selector()->start(),selector()->end());
}













void ChromosomWidget::mouseMoveEvent(QMouseEvent * event)
{
    // save cursor position
    mCursorPosition = event->pos();

    // Update cursor according to the region

    // Retrieve position in the genom
    Region region = getRegionAtPixel(mCursorPosition.x());

    // Control cursor position and find position in the region
    if (mCursorPosition.x() < mOffsetX)
    {
        mCursorPosition.setX(mOffsetX);
    }
    if (mCursorPosition.x() > mOffsetX + mChromosomWidth)
    {
        mCursorPosition.setX(mOffsetX + mChromosomWidth);
        mCursorBasePosition = region.end();
        mCursorRegion = region;
    }
    else
    {
        mCursorBasePosition = (mCursorPosition.x() - mOffsetX) / mB2PCoeff;
        mCursorRegion = region;
    }

    // Update selected region
    if (mCursorMode == select)
    {
        mFrameGhost = QRect(qMin(mCursorFirstPoint.x(), mCursorPosition.x()), 0, qAbs(mCursorFirstPoint.x()- mCursorPosition.x()), rect().height()-1);
    }
    else if ( mCursorMode == move)
    {
        int deltaMove = mCursorPosition.x() - mCursorFirstPoint.x();
        int start = mFrame.x()+deltaMove;
        if (start < mOffsetX)
        {
            start = mOffsetX;
        }
        if (start > mOffsetX + mChromosomWidth - mFrame.width())
        {
            start = mOffsetX + mChromosomWidth - mFrame.width();
        }

        mFrameGhost = QRect(start, 0, mFrame.width(), rect().height()-1);
    }
    else if ( mCursorMode == resizeL)
    {
        int start = mCursorPosition.x();
        int end = mFrame.right();

        if (start < mOffsetX)
        {
            start = mOffsetX;
        }
        if (start > end)
        {
            start = end-1;
        }

        mFrameGhost = QRect(start, 0, end - start, rect().height()-1);
    }
    else if ( mCursorMode == resizeR)
    {
        int start = mFrame.left();
        int end = mCursorPosition.x();

        if (end < start)
        {
            end = start+1;
        }
        if (end > rect().width()-mOffsetX)
        {
            end = rect().width()-mOffsetX;
        }

        mFrameGhost = QRect(start, 0, end - start, rect().height()-1);
    }

    // Refresh UI
    update();
}

void ChromosomWidget::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        mCursorFirstPoint = event->pos();

        // Constraint on the FrameFirstPoint coord
        if (mCursorFirstPoint.x() < mOffsetX) mCursorFirstPoint.setX(mOffsetX);
        if (mCursorFirstPoint.x() > mOffsetX + mChromosomWidth) mCursorFirstPoint.setX(mOffsetX + mChromosomWidth);

        // Also update the GhostFrame
        if (mFrame.contains(mCursorFirstPoint))
        {
            mFrameGhost = mFrame;
        }
        else
        {
            mFrameGhost = QRect(qMin(mCursorFirstPoint.x(), mCursorPosition.x()), 0, qAbs(mCursorFirstPoint.x()- mCursorPosition.x()), rect().height()-1);
        }

        // Handle to move the Frame
        if (mFrameHandleL.contains(event->pos()))
        {
            mCursorMode = resizeL;
        }
        else if (mFrameHandleR.contains(event->pos()))
        {
            mCursorMode = resizeR;
        }
        else if (mFrame.contains(event->pos()))
        {
            if (mCursorMode == normal)
            {
                mCursorMode = move ;
            }
            else
            {
                mCursorMode = select;
            }
        }
        else
        {
            mCursorMode = select;
        }
    }

    // Take focus to recieve keyboard event
    setFocus();

    // Refresh UI
    update();
}

void ChromosomWidget::mouseReleaseEvent(QMouseEvent *)
{
    // Save frame if action have not been canceled before (by ESC keyboard)
    if (mCursorMode != normal)
    {
        // special case for resize L/R
        if (mCursorMode == resizeL)
        {
            mSelector->setStart(pixelToBase(mFrameGhost.left()));
            updateFrame(mFrameGhost, false);
        }
        else if (mCursorMode == resizeR)
        {
            mSelector->setEnd(pixelToBase(mFrameGhost.right()));
            updateFrame(mFrameGhost, false);
        }
        else
        {
            updateFrame(mFrameGhost);
        }
    }
    mCursorMode = CursorMode::normal;

    // Refresh UI
    update();
}

void ChromosomWidget::mouseDoubleClickEvent(QMouseEvent * )
{
    // Save frame : select region and center frame on it
    Region region = getRegionAtPixel(mCursorPosition.x());
    updateFrame(QRect(baseToPixel(region.start()), 0, baseToPixel(region.end()) - baseToPixel(region.start()),rect().height()-1));

    // Refresh UI
    update();
}

void ChromosomWidget::enterEvent(QEvent *)
{
    mCursorActive = true;
    // default mode is normal, except if no region defined
    if (mSelector->start() < mSelector->end())
    {
        mCursorMode = normal;
    }
    else
    {
        mCursorMode = cutter;
    }
    update();
}

void ChromosomWidget::leaveEvent(QEvent *)
{
    mCursorActive = false;
    mCursorPosition = QPoint();
    setCursor(Qt::ArrowCursor);
    update();
}

void ChromosomWidget::keyPressEvent(QKeyEvent * event)
{
    // ESC : Back to normal : cancel all current action (selection/resizing/moving/cutter)
    if (mCursorMode != CursorMode::normal && event->key() == Qt::Key_Escape)
    {
        mCursorMode = CursorMode::normal;
        update();
    }

    // CTRL : Switch to Cutter mode
    if (event->modifiers() & Qt::ControlModifier && mCursorMode == CursorMode::normal)
    {
        mCursorMode = CursorMode::cutter;
        update();
    }
}


}}
