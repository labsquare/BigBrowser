#ifndef SELECTIONROUTER_H
#define SELECTIONROUTER_H

#include <QObject>
#include <QtCore>
#include "region.h"
namespace big {
namespace gui {
using namespace core;
/*! \class SelectionRouter
 * \brief route for selectable component
 * contains QObject with setSelection(const Region& region) as SLOT
 * and selectionChanged(const Region& region) as SIGNAL
 */
class SelectionRouter : public QObject
{
    Q_OBJECT
public:
    explicit SelectionRouter(QObject *parent = 0);
    ~SelectionRouter();
    /*!
     * \brief addComponent
     * Component is an object and must have setSelection(const Region& region) as slot
     * and selectionChanged(const Region& region) as signals
     * \param component
     */
    void addComponent(QObject * component);

public Q_SLOTS:
    /*!
     * \brief setSelection
     * Set selection for all component, except the one comming from sender()
     * \param region
     */
    void setSelection(const Region& region);
private:
    QList<QObject*> mComponent;

};

}} // end namespace
#endif // SELECTIONROUTER_H
