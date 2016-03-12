#include "abstractregionreader.h"

namespace big {
namespace core {


AbstractRegionReader::AbstractRegionReader(QIODevice *device)
    : mDevice(device)
{

}

bool AbstractRegionReader::open(QIODevice::OpenMode mode)
{
    return mDevice->open(mode);
}

void AbstractRegionReader::reset()
{
    if (mDevice->isOpen())
        mDevice->seek(0);
}

const Region &AbstractRegionReader::region()
{
    return mCurrentRegion;
}



RegionList AbstractRegionReader::regions()
{
    if (!device()->isReadable())
        qDebug()<<Q_FUNC_INFO<<"cannot read. Did you open the device?";

    device()->seek(0);
    RegionList list;
    while (next())
    {
        list.append(region());
    }
    return list;
}

QIODevice *AbstractRegionReader::device()
{
    return mDevice;
}

void AbstractRegionReader::setCurrentRegion(const Region &region)
{
    mCurrentRegion = region;
}



}}
