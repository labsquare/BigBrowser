#include <QtMath>
#include <QPainter>
#include <QDebug>
#include "rulertrack.h"
#include "sequencetrack.h"
#include "tracklistwidget.h"

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
    float width = boundingRect().width();
    // Start et end en base



    // ---------------------
    // GO
    // ---------------------
    // Calcul nombre idéal de division
    int splitFactor = qFloor(width/divIdealPxl);

    // Calcul de la taille totale en (pb) affichée
    quint64 distanceBase = end-start;

    // Avoid division by 0 error...
    if (distanceBase == 0)
    {
        painter->drawText(35,15, "Thanks to select a chromosom and a region to start.");
        painter->setBrush(Qt::BDiagPattern);
        painter->drawRect(QRect(0, 20, width, rulerHeight));
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

    // Calcul du coeff base -> pixel
    float b2pCoeff = width / distanceBase;

    // Calcul de la position en pixel de la première graudation
    int firstDivPixelStart = deltaFirstStart * b2pCoeff * -1;

    // Calcul de la taille en pixel des divisions
    int divPixelSize = divisionBaseBestStep * b2pCoeff;


    // ---------------------
    // Draw the ruler
    // ---------------------
    int pos = firstDivPixelStart;
    painter->setFont(QFont("Arial Sans", 6));
    while (pos < width)
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
    QFont font = QFont("Arial Sans", 8);
    QFontMetrics fm(font);

    const QLocale & cLocale = QLocale::c();
    QString legendText = cLocale.toString(divisionBaseBestStep);
    legendText.replace(cLocale.groupSeparator(), ' ');
    legendText += " (pb)";

    int legendWidth = fm.width(legendText);
    int legendPosition = mCursorPosition - legendWidth / 2;
    legendPosition = qMax(30, legendPosition);
    legendPosition = qMin((int) boundingRect().width() - legendWidth - 20, legendPosition);

    painter->setFont(font);
    painter->drawText(legendPosition, 15, legendText);
    painter->drawLine(legendPosition, 17, legendPosition + legendWidth, 17);
}

void RulerTrack::paintCursorLayer(QPainter * painter)
{
    mCursorPosition = mTrackList->sharedCursorX();
    painter->setPen(QColor(0,0,0,200));
    painter->drawLine(mTrackList->sharedCursorX(), 17, mTrackList->sharedCursorX(), mContentBoundaries.height());
}

}}
