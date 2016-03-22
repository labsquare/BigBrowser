#include "abstractdatamodel.h"
namespace big {
namespace core {
AbstractDataModel::AbstractDataModel(QObject *parent) : QObject(parent)
{

}

bool AbstractDataModel::isloading() const
{
    return mLoading;
}

void AbstractDataModel::setLoading(bool enable)
{
    mLoading = true;
}


}}
