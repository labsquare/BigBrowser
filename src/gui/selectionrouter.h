#ifndef SELECTIONROUTER_H
#define SELECTIONROUTER_H

#include <QObject>
#include <QtCore>
#include "region.h"
namespace big {
namespace gui {
using namespace core;

class SelectionRouter : public QObject
{
    Q_OBJECT
public:
    explicit SelectionRouter(QObject *parent = 0);
    ~SelectionRouter();
    void addComponent(QObject * component);

public Q_SLOTS:
    void setSelection(const Region& region);
private:
    QList<QObject*> mComponent;

};

}} // end namespace
#endif // SELECTIONROUTER_H
