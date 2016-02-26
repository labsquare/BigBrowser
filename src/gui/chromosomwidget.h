#ifndef CHROMOSOMWIDGET_H
#define CHROMOSOMWIDGET_H
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
class ChromosomWidget : public QWidget
{
public:
    ChromosomWidget(QWidget * parent = 0);

    void paintEvent(QPaintEvent*);
};

#endif // CHROMOSOMWIDGET_H
