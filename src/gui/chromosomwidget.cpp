#include "chromosomwidget.h"
#include "app.h"
#include <QGraphicsDropShadowEffect>

namespace big {
namespace gui {
ChromosomWidget::ChromosomWidget(const QString &filename, QWidget * parent)
    :QWidget(parent), mCytoBandFileName(filename)
{




    // Create color map
    QColor base = Qt::lightGray;

    mStains["stalk"] = Qt::darkCyan;
    mStains["gneg"] = base;
    mStains["gpos25"] = base.darker(150);
    mStains["gpos50"] = base.darker(200);
    mStains["gpos75"] = base.darker(250);
    mStains["gpos100"] =base.darker(300);
    mStains["gvar"] = Qt::darkBlue;
    mStains["acen"] = Qt::blue;








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

    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    drawChromosomWrapper(&painter);
    drawChromosom(&painter);


    //    QBrush areaBrush(QColor(255,0,0,200));
    //    areaBrush.setStyle(Qt::Dense6Pattern);
    //    painter.setBrush(areaBrush);

    //    QRect selector;
    //    selector.setLeft(mSelectorMin);
    //    selector.setRight(mSelectorMax);
    //    selector.setHeight(height());

    //    painter.drawRect(selector);
}



void ChromosomWidget::drawChromosomWrapper(QPainter *painter)
{
    // Define canvas boudaries
    float offsetX = 30;
    float offsetY = 30;
    float chromosomHeight = 30;

    float chromosomWidth = rect().width() - offsetX * 2;
    qint64 maxBase = mChromosoms.last().last();
    float drawCoeff = chromosomWidth / maxBase;

    // Chromosom wrapper parameters
    float endPart1 = 0;
    float startPart2 = 0;
    float centX = 0;
    int wrapperPadding = 2;
    int wrc = 5; // wrapperRoundCoeff : pixel distance used by spline anchores

    // Init paint objects
    painter->setBrush(Qt::black);

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
    offsetX -= wrapperPadding;
    offsetY -= wrapperPadding;
    QPoint A(offsetX, offsetY);
    QPoint B(offsetX + endPart1 + 2* wrapperPadding, offsetY);
    QPoint C(offsetX + centX, offsetY + chromosomHeight / 2 - 5 );
    QPoint D(offsetX + startPart2, offsetY);
    QPoint E(offsetX + chromosomWidth + 2* wrapperPadding , offsetY);

    offsetY += 2 * wrapperPadding + chromosomHeight;
    QPoint F(offsetX + chromosomWidth + 2* wrapperPadding, offsetY);
    QPoint G(offsetX + startPart2, offsetY);
    QPoint H(offsetX + centX, offsetY - chromosomHeight / 2 + 5);
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

    painter->setBrush(Qt::lightGray);
    painter->setPen(Qt::darkGray);
    painter->drawPath(path);

}





void ChromosomWidget::drawChromosom(QPainter *painter)
{
    // Is there something to draw ?
    if (mChromosoms.isEmpty())
        return;

    // Define canvas boudaries
    float offsetX = 30;
    float offsetY = 30;
    float chromosomHeight = 30;

    float chromosomWidth = rect().width() - offsetX * 2;
    qint64 maxBase = mChromosoms.last().last();
    float drawCoeff = chromosomWidth / maxBase;

    // Init paint objects
    painter->setBrush(Qt::black);

    // Loop to draw regions
    foreach ( Region region, mChromosoms)
    {
        // Define region
        QString stain = region.data("stain").toString();
        QRect fragment;

        float regionWidth = region.length() * drawCoeff;
        float regionStart = offsetX + region.first() * drawCoeff;


        if (stain == "acen" || stain == "gvar")
        {
            fragment.setTopLeft(QPoint(regionStart, offsetY + chromosomHeight / 2 - 5));
            fragment.setWidth(regionWidth);
            fragment.setHeight(10);
        }
        else
        {
            fragment.setTopLeft(QPoint(regionStart,offsetY));
            fragment.setWidth(regionWidth);
            fragment.setHeight(chromosomHeight);
        }

        // Draw the region
        painter->setBrush(mStains.value(region.data("stain").toString(),Qt::red));
        painter->setPen(QPen(Qt::white));
        painter->drawRect(fragment);

        // Draw region label

        fragment.setTopLeft(QPoint(regionStart + chromosomHeight + 10,offsetY));
        painter->setPen(QPen(Qt::red));
        //painter->rotate(90);
        painter->drawText(fragment, Qt::AlignCenter,region.name());

    }
}



}}
