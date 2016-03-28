#include "selectionrouter.h"
namespace big {
namespace gui {
SelectionRouter::SelectionRouter(QObject *parent) : QObject(parent)
{

}

SelectionRouter::~SelectionRouter()
{
    qDeleteAll(mObjects);
}


void SelectionRouter::addObject(QObject *obj)
{
    mObjects.append(obj);
    connect(obj,  SIGNAL(selectionChanged(Selection)),
            this, SLOT(setSelection(Selection)));
}



void SelectionRouter::setSelection(const Selection &selection)
{

    foreach ( QObject * obj , mObjects)
    {
        if (obj != sender())
        {
            QMetaObject::invokeMethod(obj,"setSelection",Q_ARG(Selection,selection));
        }
    }
}

}} // end namespace
