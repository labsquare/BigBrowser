#include "chromosomwidget.h"

ChromosomWidget::ChromosomWidget(QWidget * parent)
    :QWidget(parent)
{

}

void ChromosomWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

}
