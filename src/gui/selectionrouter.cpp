#include "selectionrouter.h"
namespace big {
namespace gui {
SelectionRouter::SelectionRouter(QObject *parent) : QObject(parent)
{

}

void SelectionRouter::addObject(QObject *obj)
{
    mObjects.append(obj);
    connect(obj,  SIGNAL(selectionChanged(Selection)),
            this, SLOT(setSelection(Selection)));

}



void SelectionRouter::setSelection(const Selection &selection)
{
    qDebug()<<Q_FUNC_INFO<<"set selection ";

    foreach ( QObject * obj , mObjects)
    {
        if (obj != sender())
        {
            QMetaObject::invokeMethod(obj,"setSelection",Q_ARG(Selection,selection));
        }
    }
}

}} // end namespace
