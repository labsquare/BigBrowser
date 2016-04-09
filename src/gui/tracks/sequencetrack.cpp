#include <QApplication>
#include <QtMath>
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include "app.h"
#include "sequencetrack.h"
#include "sequencetrack.h"
#include "trackswidget.h"

namespace big {
namespace gui {

SequenceTrack::SequenceTrack(QGraphicsItem * parent)
    :AbstractTrack(parent)
{
    setHeight(37);
    setResizable(false);

    // Generate fake sequence
    // ToDo : to replace by the true sequence retrieved asynch
    QString bases = "ACGT";
    for (int i=0; i<1000; i++)
    {

        mFakeSequence += bases[qrand() % 4];
    }
}


void SequenceTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{
    if (mTrackList->sharedCursorBaseW() >= 8)
    {
        QFont font = QFont("Arial Sans", 8, 63);
        baseWidthToFont(mTrackList->sharedCursorBaseW(), &font);
        painter->setFont(font);

        int baseIdx = start % mFakeSequence.length();
        float pxlPos = mTrackList->base2PixelFrame(start) + mTrackList->trackContentStartX();
        float pxlEnd = mTrackList->selectionW() + mTrackList->trackContentStartX() + mTrackList->sharedCursorBaseW();
        while (pxlPos < pxlEnd)
        {
            QChar letter = mFakeSequence[baseIdx];
            baseIdx = baseIdx + 1 % mFakeSequence.length();

            painter->setPen(baseToColor(letter));
            painter->drawText(pxlPos, 30, letter);
            pxlPos += mTrackList->sharedCursorBaseW();
        }
    }

    if (mTrackList->sharedCursorBaseW() > 1)
    {
        int baseIdx = start % mFakeSequence.length();
        float pxlPos = mTrackList->base2PixelFrame(start) + mTrackList->trackContentStartX();
        float pxlEnd = mTrackList->selectionW() + mTrackList->trackContentStartX() + mTrackList->sharedCursorBaseW();
        while (pxlPos < pxlEnd)
        {
            QChar letter = mFakeSequence[baseIdx];
            baseIdx = baseIdx + 1 % mFakeSequence.length();

            painter->setPen(baseToColor(letter));
            painter->setBrush(baseToColor(letter));
            painter->drawRect(pxlPos, 33, mTrackList->sharedCursorBaseW(), 3);
            pxlPos += mTrackList->sharedCursorBaseW();
        }
    }
}




void SequenceTrack::paintCursorLayer(QPainter * painter)
{
    QColor baseColor = qApp->style()->standardPalette().highlight().color();

    // Do we need to display the magnifier ?
    if (C_MAGNIFIER_ENABLE && mTrackList->sharedCursorBaseW() < 8)
    {
        QFont font = QFont("Arial Sans", 8, 63);
        baseWidthToFont(mTrackList->C_BASE_MAX_PIXEL_WIDTH, &font);
        painter->setFont(font);

        // Get start position of the magnifier
        quint64 start = mTrackList->sharedCursorPosB() - C_MAGNIFIER_BASE_WIDTH;
        start = start > mTrackList->sharedCursorPosB() ? 0 : start;

        // Get end position of the magnifier
        quint64 end = mTrackList->sharedCursorPosB() + C_MAGNIFIER_BASE_WIDTH;
        end = qMin(end, mTrackList->selection().end());

        // Get pxl position where magnifier start
        float pxlPos = mTrackList->sharedCursorPosX() - C_MAGNIFIER_BASE_WIDTH / 2.0 - (mTrackList->sharedCursorPosB() - start) * C_MAGNIFIER_BASE_WIDTH;
        pxlPos = qMax ((float)0, pxlPos);

        qDebug() << "start : " << start << " end : " << end << " -- : " << end - start;
        float pxlEnd = pxlPos + (end - start) * mTrackList->C_BASE_MAX_PIXEL_WIDTH;
        //pxlEnd = qMin (mTrackList->selectionW() - (end - start) * C_MAGNIFIER_BASE_WIDTH, pxlEnd);


/*
        int baseIdx = start % mFakeSequence.length();
        float pxlPos = mTrackList->base2PixelFrame(start) + mTrackList->trackContentStartX();
        float pxlEnd = mTrackList->selectionW() + mTrackList->trackContentStartX() + mTrackList->sharedCursorBaseW();
        while (pxlPos < pxlEnd)
        {
            QChar letter = mFakeSequence[baseIdx];
            baseIdx = baseIdx + 1 % mFakeSequence.length();

            painter->setPen(baseToColor(letter));
            painter->drawText(pxlPos, 30, letter);
            pxlPos += mTrackList->sharedCursorBaseW();
        }
*/
        int startCursor = mTrackList->sharedCursorBaseX() + mTrackList->trackContentStartX();
        int endCursor = startCursor + mTrackList->sharedCursorBaseW();
        QPointF points[12] = {
            QPointF(startCursor, 0),
            QPointF(startCursor, 5),
            QPointF(pxlPos, 10),
            QPointF(pxlPos, 25),
            QPointF(startCursor, 30),
            QPointF(startCursor, height()),

            QPointF(endCursor, height()),
            QPointF(endCursor, 30),
            QPointF(pxlEnd, 25),
            QPointF(pxlEnd, 10),
            QPointF(endCursor, 5),
            QPointF(endCursor, 0),
        };


        painter->setPen(baseColor);
        QColor bg = baseColor.lighter(150);
        bg.setAlpha(100);
        painter->setBrush(bg);
        painter->drawPolygon(points, 12);

        /*
        int baseIdx = start % mFakeSequence.length();
        float pxlPos = mTrackList->base2PixelFrame(start) + mTrackList->trackContentStartX();
        float pxlEnd = mTrackList->selectionW() + mTrackList->trackContentStartX() + mTrackList->sharedCursorBaseW();
        while (pxlPos < pxlEnd)
        {
            QChar letter = mFakeSequence[baseIdx];
            baseIdx = baseIdx + 1 % mFakeSequence.length();

            painter->setPen(baseToColor(letter));
            painter->setBrush(baseToColor(letter));
            painter->drawRect(pxlPos, 50, mTrackList->sharedCursorBaseW(), 5);
            pxlPos += mTrackList->sharedCursorBaseW();
        }*/
    }
    else
    {
        painter->setPen(baseColor);


        int startCursor = mTrackList->sharedCursorBaseX() + mTrackList->trackContentStartX();
        if (mTrackList->sharedCursorBaseW() > 2)
        {
            QColor bg = baseColor.lighter(150);
            bg.setAlpha(100);
            painter->setBrush(bg);
            painter->drawRect(startCursor, 0, mTrackList->sharedCursorBaseW(), boundingRectContent().height());
        }
        else
        {
            painter->drawLine(startCursor, 0, startCursor, boundingRectContent().height());
        }
    }
}

















QColor SequenceTrack::baseToColor(QChar base)
{
    if(base == 'A')
    {
            return C_COLOR_A;
    }
    else if(base == 'T')
    {
        return C_COLOR_T;
    }
    else if(base == 'G')
    {
        return C_COLOR_G;
    }
    else if(base == 'C')
    {
        return C_COLOR_C;
    }
    return Qt::black;
}

void SequenceTrack::baseWidthToFont(float baseWidth, QFont * font)
{
    font->setPointSizeF(baseWidth);
    return;

    QFontMetrics fm(*font);
    float factor = baseWidth / fm.width('G'); // we G as it's the largest letter among ACGT
    if ((factor < 1) || (factor > 1.25))
    {
        font->setPointSizeF(font->pointSizeF() * factor);
    }
}


}} // end namespace
