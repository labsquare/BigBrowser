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

    mBaseColors = {
        {'A',QColor(50,100,200)},
        {'T',QColor(230,160,60)},
        {'G',QColor(100,200,120)},
        {'C',QColor(200,80,80)}
    };

    // Generate fake sequence
    // ToDo : to replace by the true sequence retrieved asynch
    QString bases = "ACGT";
    for (int i=0; i<1000; i++)
    {
        mFakeSequence.append(bases.toUtf8().at(qrand() % 4));
    }
}


void SequenceTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{
    // Display base if possible
    if (mTrackList->sharedCursorBaseW() > 1)
    {
        // Set font
        QFont font = QFont("Arial Sans", 8, 63);
        baseWidthToFont(mTrackList->sharedCursorBaseW(), &font);
        painter->setFont(font);

        int baseIdx = start % mFakeSequence.length();
        float pxlPos = mTrackList->base2PixelFrame(start) + mTrackList->trackContentStartX();
        float pxlEnd = mTrackList->selectionW() + mTrackList->trackContentStartX() + mTrackList->sharedCursorBaseW();
        while (pxlPos < pxlEnd)
        {
            char letter = mFakeSequence.at(baseIdx);
            baseIdx = baseIdx + 1 % mFakeSequence.length();


            painter->setPen(baseToColor(letter));
            painter->setBrush(baseToColor(letter));
            painter->drawRect(pxlPos, 33, mTrackList->sharedCursorBaseW(), 3);

            // Display base letter only if there is enough space
            if (mTrackList->sharedCursorBaseW() >= 8)
            {
                painter->setPen(baseToColor(letter));
                painter->drawText(pxlPos, 30, QChar(letter));
            }

            pxlPos += mTrackList->sharedCursorBaseW();
        }
    }
}




void SequenceTrack::paintCursorLayer(QPainter * painter)
{
    QColor baseColor = qApp->style()->standardPalette().highlight().color();

    // Do we need to display the magnifier ?
    if (C_MAGNIFIER_ENABLE && mTrackList->sharedCursorBaseW() < 8 && mTrackList->sharedCursorBaseW() > 1)
    {

        // Get start base position of the magnifier
        quint64 magnifierStartB = mTrackList->sharedCursorPosB() - C_MAGNIFIER_BASE_WIDTH;
        magnifierStartB = magnifierStartB > mTrackList->sharedCursorPosB() ? 0 : magnifierStartB;
        int magnifierDeltaStartB = mTrackList->sharedCursorPosB() - magnifierStartB;

        // Get end base position of the magnifier
        quint64 magnifierEndB = mTrackList->sharedCursorPosB() + C_MAGNIFIER_BASE_WIDTH;
        magnifierEndB = qMin(magnifierEndB, mTrackList->selection().end());
        int magnifierDeltaEndB = magnifierEndB - mTrackList->sharedCursorPosB();

        // Compute pxl position where magnifier start
        float magnifierCursorStartX = mTrackList->sharedCursorBaseX() + mTrackList->sharedCursorBaseW()/2.0 - mTrackList->C_BASE_MAX_PIXEL_WIDTH / 2.0;
        float magnifierStartX = magnifierCursorStartX - magnifierDeltaStartB * C_MAGNIFIER_BASE_WIDTH;
        magnifierStartX = qMax ((float)0, magnifierStartX);
        QRectF magnifierRect(mTrackList->sharedCursorBaseX() + mTrackList->sharedCursorBaseW()/2.0 - mTrackList->C_BASE_MAX_PIXEL_WIDTH / 2 - 1
                             , 10
                             , mTrackList->C_BASE_MAX_PIXEL_WIDTH + 2
                             , 17);


        // Shift referentiel : from frame pixel positions to track pixel position
        magnifierCursorStartX +=  mTrackList->trackContentStartX();
        magnifierRect.translate(mTrackList->trackContentStartX(), 0);

        // Draw selection frame
        int startCursor = mTrackList->sharedCursorBaseX() + mTrackList->trackContentStartX();
        int endCursor = startCursor + mTrackList->sharedCursorBaseW();

        painter->setPen(baseColor);
        QColor bg = baseColor.lighter(150);
        bg.setAlpha(100);
        painter->setBrush(bg);

        painter->drawRect(startCursor, 0, mTrackList->sharedCursorBaseW(), 10);
        painter->drawRect(startCursor, 27, mTrackList->sharedCursorBaseW(), height() - 27);
        painter->drawEllipse(magnifierRect);

        // Draw letter under magnifier
        int baseIdx = mTrackList->sharedCursorPosB() % mFakeSequence.length();
        char letter = mFakeSequence.at(baseIdx);
        QColor letterColor = baseToColor(letter);
        QFont font = QFont("Arial Sans", 9, 63);
        painter->setFont(font);
        painter->setPen(letterColor);
        painter->drawText(magnifierRect, Qt::AlignHCenter | Qt::AlignVCenter, QChar(letter));

        QRectF letterArea = magnifierRect;
        letterArea.setWidth(mTrackList->C_BASE_MAX_PIXEL_WIDTH);
        letterArea.translate(-magnifierRect.width(),0);
        float alphaStep = 200.0 / magnifierDeltaStartB;
        //qDebug() << alphaStep ;
        for (int i=1; i < magnifierDeltaStartB; i++)
        {
            baseIdx = (mTrackList->sharedCursorPosB() - i) % mFakeSequence.length();
            char letter = mFakeSequence.at(baseIdx);
            QColor letterColor = baseToColor(letter);
            QFont font = QFont("Arial Sans", 9, 63);
            letterColor.setAlpha(255 - i * alphaStep);
            painter->setFont(font);
            painter->setPen(letterColor);
            painter->drawText(letterArea, Qt::AlignHCenter | Qt::AlignVCenter, QChar(letter));
            letterArea.translate(-mTrackList->C_BASE_MAX_PIXEL_WIDTH, 0);
        }

        letterArea = magnifierRect;
        letterArea.setWidth(mTrackList->C_BASE_MAX_PIXEL_WIDTH);
        letterArea.translate(magnifierRect.width(),0);
        alphaStep = 200.0 / magnifierDeltaEndB;
        for (int i=1; i < magnifierDeltaStartB; i++)
        {
            baseIdx = (mTrackList->sharedCursorPosB() + i) % mFakeSequence.length();
            char letter = mFakeSequence.at(baseIdx);
            QColor letterColor = baseToColor(letter);
            QFont font = QFont("Arial Sans", 9, 63);
            letterColor.setAlpha(255 - i * alphaStep);
            painter->setFont(font);
            painter->setPen(letterColor);
            painter->drawText(letterArea, Qt::AlignHCenter | Qt::AlignVCenter, QChar(letter));
            letterArea.translate(mTrackList->C_BASE_MAX_PIXEL_WIDTH, 0);
        }
        /*
        if (baseIdx < magnifierDeltaStartB)
        letterColor.setAlpha(255);

        float letterPos = magnifierStartX;
        for (int baseIdx = 0; baseIdx <= magnifierDeltaStartB + magnifierDeltaEndB; baseIdx++)
        {


            // Set color and opacity of the letter


            // Display
            painter->setPen(letterColor);
            painter->drawText(letterPos, 23, letter);
            letterPos += mTrackList->C_BASE_MAX_PIXEL_WIDTH;
        }*/
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

















QColor SequenceTrack::baseToColor(char base)
{
    return mBaseColors.value(base, Qt::black);
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
