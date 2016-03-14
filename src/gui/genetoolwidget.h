#ifndef GENETOOLWIDGET_H
#define GENETOOLWIDGET_H
#include <QWidget> // base class for all gui component
#include <QPainter> // to paint
#include <QMouseEvent> // To get mouse feature
namespace big {

namespace gui {

class GeneToolWidget : public QWidget
{
public:
    // constructor
    GeneToolWidget(QWidget * parent = 0);

protected:
    // This methods is a QWidget methods, call each time the widgets need to redraw something
    // For exemple, during resizing, or at the start
    virtual void paintEvent(QPaintEvent * event);

    // This methods is a QWidget methods, called when you click on the widget
    virtual void mousePressEvent(QMouseEvent * event);

private:
    // Here private atributes. Each name start with a m
    QString mAttribut;

};


}} // end namespace

#endif // GENETOOLWIDGET_H
