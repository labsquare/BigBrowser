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
    ~SelectionRouter();
    /*!
     * \brief addObject
     * append object with signals and slots :
     *  > setSelection(Selection&)
     *  > selectionChanged(Selection&)
     * \param obj
     */
    void addObject(QObject * obj);


public Q_SLOTS:
    /*!
 * \brief setSelection
 * call setSelection for all objects, except from the sender
 * \param selection
 */
void setSelection(const Selection& selection);


private:

    QList<QObject *> mObjects;



};

}} // end namespace

#endif // SELECTIONROUTER_H
