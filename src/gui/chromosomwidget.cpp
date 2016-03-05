#include "chromosomwidget.h"
#include "app.h"
#include <QGraphicsDropShadowEffect>

namespace big {
namespace gui {
ChromosomWidget::ChromosomWidget(const QString &filename, QWidget * parent)
    :QWidget(parent), mCytoBandFileName(filename)
{




    // Create color map
    QColor base = QColor(200,200,200);

    mStains["stalk"] = Qt::darkCyan;
    mStains["gneg"] = base;
    mStains["gpos25"]  = base.darker(100);
    mStains["gpos50"]  = base.darker(150);
    mStains["gpos75"]  = base.darker(200);
    mStains["gpos100"] = base.darker(250);
    mStains["gvar"] = QColor(144, 195, 212);
    mStains["acen"] = QColor(80, 144, 212);








}

void ChromosomWidget::setChromosom(const QString &chromosom)
{
    CytobandReader mReader(mCytoBandFileName);

    if (mReader.open())
    {
        mChromosoms.clear();

        while (mReader.next())
        {
            if (mReader.region().chromosom() == chromosom )
                mChromosoms.append(mReader.region());
        }

        mRegionSelector.setChromosom(chromosom);

    }


    qDebug()<<chromosom<<" "<<mChromosoms.count();
    update();


}

void ChromosomWidget::setRange(qint64 start, qint64 end)
{
    mRegionSelector.setRange(start, end);
}


void ChromosomWidget::paintEvent(QPaintEvent *)
{
    // Is there something to draw ?
    if (mChromosoms.isEmpty())
    {
        // Todo draw empty screen error : something like the genome of the "anthropopitheque" ;)
        return;
    }


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




    // Now merge the parts
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(rect(), img1);
    painter.drawImage(rect(), img2);
    painter.drawImage(rect(), img3);


}



//int wrapperPadding = 2;
//int wrc = 5; // wrapperRoundCoeff : pixel distance used by spline anchores
QPainterPath ChromosomWidget::getChromosomWrapperShape(int wrapperPadding, int wrc) const
{
    float chromosomWidth = rect().width() - mOffsetX * 2;
    qint64 maxBase = mChromosoms.last().last();
    float drawCoeff = chromosomWidth / maxBase;

    // Chromosom wrapper parameters
    float endPart1 = 0;
    float startPart2 = 0;
    float centX = 0;

    // Compute centromere special coordinates
    foreach ( Region region, mChromosoms)
    {
        QString stain = region.data("stain").toString();

        if(stain == "acen" && endPart1 == 0)
        {
            endPart1 = region.first() * drawCoeff;
            centX = region.last() * drawCoeff;
        }
        else if (endPart1 > 0  && stain != "acen" && startPart2 == 0)
        {
            startPart2 = region.first() * drawCoeff;
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
    QPoint E(offsetX + chromosomWidth + 2* wrapperPadding , offsetY);

    offsetY += 2 * wrapperPadding + mChromosomHeight;
    QPoint F(offsetX + chromosomWidth + 2* wrapperPadding, offsetY);
    QPoint G(offsetX + startPart2, offsetY);
    QPoint H(offsetX + centX, offsetY - mChromosomHeight / 2 + 5);
    QPoint I(offsetX + endPart1 + 2* wrapperPadding, offsetY);
    QPoint J(offsetX, offsetY );


    // Drawing chromosom wrapper
    QPainterPath path;

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

    // Job done
    return path;
}





void ChromosomWidget::drawRegions(QPainter *painter)
{
    // Define canvas boudaries
    float chromosomWidth = rect().width() - mOffsetX * 2;
    qint64 maxBase = mChromosoms.last().last();
    float drawCoeff = chromosomWidth / maxBase;

    /*
    mStains["stalk"] = Qt::darkCyan;
    mStains["gneg"] = base;
    mStains["gpos25"]  = base.darker(100);
    mStains["gpos50"]  = base.darker(150);
    mStains["gpos75"]  = base.darker(200);
    mStains["gpos100"] = base.darker(250);
    mStains["gvar"] = QColor(144, 195, 212);
    mStains["acen"] = QColor(80, 144, 212);
    */




    // Loop to draw regions
    foreach ( Region region, mChromosoms)
    {
        float regionWidth = region.length() * drawCoeff;
        float regionStart = mOffsetX + region.first() * drawCoeff;

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
    float chromosomWidth = rect().width() - mOffsetX * 2;
    qint64 maxBase = mChromosoms.last().last();
    float drawCoeff = chromosomWidth / maxBase;
    int offsetY = mOffsetY + mChromosomHeight - 1 ;

    painter->setPen(QPen(QColor(50,50,50)));
    painter->setFont(QFont("Arial", 7));

    // Loop to draw labels
    foreach ( Region region, mChromosoms)
    {
        float regionWidth = region.length() * drawCoeff;
        float regionStart = mOffsetX + region.first() * drawCoeff;



        // Draw bounds lines
        //painter->drawLine(regionStart, mOffsetY, regionStart, offsetY + 50);
        //painter->drawLine(regionStart + regionWidth, mOffsetY, regionStart + regionWidth, offsetY + 50);
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
    painter->drawLine(mOffsetX + chromosomWidth, mOffsetY, mOffsetX + chromosomWidth, offsetY );
}



}}
