#include "tracksettingsheader.h"
#include <QApplication>
#include <QStyle>
#include <QDebug>
#include <QStyleOption>
#include <QPalette>
#include "app.h"
namespace big {
namespace gui {
TrackSettingsHeader::TrackSettingsHeader(QWidget *parent) :
    QWidget(parent),
    mTitle("No Title"),
    mIsExpand(true)
{


    setFixedHeight(26);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    mAngle.setStartValue(-90);
    mAngle.setEndValue(0);
    mAngle.setDuration(200);
    mAngle.setEasingCurve(QEasingCurve::OutCurve);

    connect(&mAngle,SIGNAL(valueChanged(QVariant)),this,SLOT(update()));

}

void TrackSettingsHeader::setExpand(bool expand)
{

    if (mAngle.state() == QAbstractAnimation::Running)
        mAngle.stop();

    if (!expand)
        mAngle.setDirection(QAbstractAnimation::Forward);
    else
        mAngle.setDirection(QAbstractAnimation::Backward);


    mIsExpand = expand;
    mAngle.start();

    emit expandChanged(expand);


}

bool TrackSettingsHeader::isExpand() const
{
 return mIsExpand;
}

void TrackSettingsHeader::paintEvent(QPaintEvent *event)
{

    // draw the background header
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(qApp->style()->standardPalette().shadow());
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect());

    // draw title
    QFont font = qApp->font();
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(QPen(qApp->style()->standardPalette().brightText().color()));
    QRect textArea = rect().adjusted(height()/2 + 10,0,0,0);
    painter.drawText(textArea, Qt::AlignLeft|Qt::AlignVCenter, mTitle);


    // draw arrow

    painter.save();

    QStyleOption option;
    option.rect = QRect(0,0,height(),height());
    option.palette.setBrush(QPalette::Foreground, Qt::lightGray);

    // do rotation
    painter.translate(option.rect.center());
    painter.rotate(mAngle.currentValue().toInt());
    painter.translate(-option.rect.center());

    qApp->style()->drawPrimitive(QStyle::PE_IndicatorArrowDown,&option, &painter);

    painter.restore();


    painter.setPen(QPen(qApp->style()->standardPalette().shadow().color().dark()));
    painter.drawLine(0,height(), width(), height());

    painter.setPen(QPen(qApp->style()->standardPalette().shadow().color().light()));
    painter.drawLine(0,0, width(), 0);
}

void TrackSettingsHeader::mousePressEvent(QMouseEvent *event)
{

    setExpand(!isExpand());


}


}} // end namespace
