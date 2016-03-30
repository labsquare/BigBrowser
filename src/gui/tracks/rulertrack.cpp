#include <QApplication>
#include <QtMath>
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include "app.h"
#include "rulertrack.h"
#include "sequencetrack.h"
#include "trackswidget.h"

namespace big {
namespace gui {


RulerTrack::RulerTrack(QGraphicsItem * parent)
    :AbstractTrack(parent)
{
    setHeight(25);
    setResizable(false);


    // Todo :
    //  - No option (disable settings button)
    //  - Set Default Title of the track : "Ruler" (this title should be displayed when drag&droping tracks)

}



void RulerTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{

    // Todo : translate in english comment
    painter->setPen(Qt::black);

    // ---------------------
    // INPUTS
    // ---------------------
    int rulerHeight = 5;
    // Taille idéale en pixel recherchée pour les divisions de la règle
    int divIdealPxl = 150;
    // Taille de la règle en pixel
    float width = boundingRectContent().width();
    // Start et end en base
    int startX = boundingRectContent().left();


    // ---------------------
    // GO
    // ---------------------
    // Calcul nombre idéal de division
    int splitFactor = qFloor(width/divIdealPxl);

    // Calcul de la taille totale en (pb) affichée
    quint64 distanceBase = mTrackList->selectionD();

    // Avoid division by 0 error...
    if (distanceBase == 0)
    {
        painter->drawText(35,15, "Thanks to select a chromosom and a region to start.");
        painter->setBrush(Qt::BDiagPattern);
        painter->drawRect(QRect(startX, 20, width, rulerHeight));
        return;
    }

    // Calcul Taille en (pb) de la "Division Idéale"
    double value = distanceBase/splitFactor;
    quint64 divIdealBase = (quint64) value;
    // Calcul de la puissance de 10 la plus proche
    qint64 divisionBaseBestStep = qPow(10, QString::number(divIdealBase).length() - 1);
    value = divIdealBase / divisionBaseBestStep;
    divisionBaseBestStep = qCeil(value) * divisionBaseBestStep;


    // Calcul de la position en (bp) de la première graduation
    int deltaDivNumber = qFloor(start/divisionBaseBestStep);
    quint64 min64 = 0;
    quint64 deltaFirstStart = qMax(min64, start-deltaDivNumber*divisionBaseBestStep);
    quint64 firstDivBaseStart = start - deltaFirstStart;

    // Calcul de la couleur de la première graduation : 0=blanc, 1=noir
    bool deltaDivColor = deltaDivNumber % 2;


    // Calcul de la position en pixel de la première graudation
    int firstDivPixelStart = mTrackList->base2PixelFrame(firstDivBaseStart);
    // Calcul de la taille en pixel des divisions
    int divPixelSize = mTrackList->base2PixelFrame(firstDivBaseStart + divisionBaseBestStep) - firstDivPixelStart;

    /*
    if (mTrackList->sharedCursorBaseW() > 1)
    {
        divisionBaseBestStep++;
        divPixelSize = mTrackList->sharedCursorBaseW() * divisionBaseBestStep;
    }
*/
    //qDebug() << "firstDivPixelStart : " << firstDivPixelStart << " divPixelSize : " << divPixelSize << " divisionBaseBestStep : " << divisionBaseBestStep << " sharedCursorBaseW : " << mTrackList->sharedCursorBaseW();


    // ---------------------
    // Draw the ruler
    // ---------------------
    int pos = firstDivPixelStart + mTrackList->trackContentStartX();
    painter->setFont(QFont("Arial Sans", 6));
    while (pos < boundingRect().width())
    {
        // Draw legend
        const QLocale & cLocale = QLocale::c();
        QString ss = cLocale.toString(firstDivBaseStart);
        ss.replace(cLocale.groupSeparator(), ' ');
        painter->drawText(pos+2,18, ss);
        firstDivBaseStart +=divisionBaseBestStep;

        QColor col = deltaDivColor?QColor(0,0,0,150):QColor(255,255,255);
        painter->setBrush(col);
        painter->drawRect(QRect(pos, 20, divPixelSize, rulerHeight));
        // painter->drawLine(pos, 20,pos, boundingRect().height());

        // Next division
        pos+=divPixelSize;
        deltaDivColor = !deltaDivColor;
    }

    // Draw Current position
    QColor baseColor = qApp->style()->standardPalette().highlight().color();
    painter->setPen(baseColor);
    QFont font = QFont("Arial Sans", 9, 63);
    QFontMetrics fm(font);

    const QLocale & cLocale = QLocale::c();
    QString legendText = cLocale.toString(mTrackList->sharedCursorPosB());
    legendText.replace(cLocale.groupSeparator(), ' ');
    legendText += " (pb)";

    int legendWidth = fm.width(legendText);
    int legendPosition = mTrackList->sharedCursorPosX() - legendWidth / 2 + mTrackList->trackContentStartX();
    legendPosition = qMax(mTrackList->trackContentStartX(), legendPosition);
    legendPosition = qMin(mTrackList->selectionW() + mTrackList->trackContentStartX() - legendWidth, legendPosition);

    painter->setBrush(Qt::white);
    painter->setPen(Qt::NoPen);
    painter->drawRect(legendPosition-3,1, legendWidth+6, 19);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->drawText(legendPosition, 15, legendText);
}

void RulerTrack::paintCursorLayer(QPainter * painter)
{
    QColor baseColor = qApp->style()->standardPalette().highlight().color();
    painter->setPen(baseColor);

    int startCursor = mTrackList->sharedCursorBaseX() + mTrackList->trackContentStartX();
    if (mTrackList->sharedCursorBaseW() > 2)
    {
        QColor bg = baseColor.lighter(150);
        bg.setAlpha(100);
        painter->setBrush(bg);
        painter->drawRect(startCursor, 18, mTrackList->sharedCursorBaseW(), 7);
    }
    else
    {
        painter->drawLine(startCursor, 17, startCursor, boundingRectContent().height());
    }

}

}}
