#ifndef SELECTIONROUTER_H
#define SELECTIONROUTER_H

#include <QObject>
#include <QList>
#include "selection.h"
namespace big {
namespace gui {
using namespace core;

class SelectionRouter : public QObject
{
    Q_OBJECT
public:
    explicit SelectionRouter(QObject *parent = 0);
    void addObject(QObject * obj);

Q_SIGNALS:

protected Q_SLOTS:
void setSelection(const Selection& selection);


private:

    QList<QObject *> mObjects;



};

}} // end namespace

#endif // SELECTIONROUTER_H
