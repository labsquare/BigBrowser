#include "genetoolwidget.h"
#include <QDebug>
namespace big {
namespace gui {
// Constructor
GeneToolWidget::GeneToolWidget(QWidget * parent)
    :QWidget(parent)
{
    // init start attribute
    mAttribut = "Plopp";

}

void GeneToolWidget::paintEvent(QPaintEvent *event)
{
    // Tell to draw something on the widget
    QPainter painter(this);
    // Like paint on windows.. Set a brush and a pen
    painter.setBrush(QBrush(Qt::red));
    painter.setPen(QPen(Qt::blue));

    // draw a rectangle on the widget
    painter.drawRect(rect().adjusted(40,40,-40,-40));

}

void GeneToolWidget::mousePressEvent(QMouseEvent *event)
{
        qDebug()<<"you click here "<<event->pos();
}


}} // end namespace
