#include "selectionrouter.h"
namespace big {
namespace gui {

SelectionRouter::SelectionRouter(QObject *parent)
    : QObject(parent)
{

}

SelectionRouter::~SelectionRouter()
{
    mComponent.clear();
}

void SelectionRouter::addComponent(QObject *component)
{
    mComponent.append(component);
    connect(component,SIGNAL(selectionChanged(Region)),
            this,     SLOT(setSelection(Region)));
}

void SelectionRouter::setSelection(const Region &region)
{
    foreach ( QObject * component , mComponent)
    {
        if (component != sender())
        {
            bool success = QMetaObject::invokeMethod(component,"setSelection",Q_ARG(Region,region));
            if (!success)
                qWarning()<<Q_FUNC_INFO<<"cannot invoke Method setSelection on "<<component;
        }
    }
}


}} // end namespace
