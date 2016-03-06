#include "abstractregionreader.h"

namespace big {
namespace core {


AbstractRegionReader::AbstractRegionReader(QIODevice *device)
    : mDevice(device),mCurrentLine(0)
{


}

AbstractRegionReader::AbstractRegionReader(const QString &filename)
    :mDevice(new QFile(filename)),mCurrentLine(0)
{



}

quint64 AbstractRegionReader::currentLine() const
{
    return mCurrentLine;
}

bool AbstractRegionReader::open(QIODevice::OpenMode mode)
{
    return mDevice->open(mode);
}

void AbstractRegionReader::reset()
{
    setCurrentLine(0);
    if (mDevice->isOpen())
        mDevice->seek(0);
}

const Region &AbstractRegionReader::region() const
{
    return  mRegion;
}

RegionList AbstractRegionReader::regions()
{

    if (!device()->isOpen())
        device()->open(QIODevice::ReadOnly);

    RegionList list;
    while (next())
    {
        list.append(region());
    }

    device()->close();
    return list;
}

bool AbstractRegionReader::isValid()
{
    return device()->isOpen();
}



QIODevice *AbstractRegionReader::device()
{
    return mDevice;
}


void AbstractRegionReader::setRegion(const Region &region)
{
    mRegion = region;
}

void AbstractRegionReader::setCurrentLine(quint64 line)
{
    mCurrentLine = line;
}

}}
