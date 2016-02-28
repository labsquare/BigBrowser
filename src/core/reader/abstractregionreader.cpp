#include "abstractregionreader.h"

namespace big {
namespace core {


AbstractRegionReader::AbstractRegionReader(QIODevice *device)
    :mCurrentLine(0), mDevice(device)
{

}

AbstractRegionReader::AbstractRegionReader(const QString &filename)
    :mCurrentLine(0), mDevice(new QFile(filename))
{

}

qint64 AbstractRegionReader::currentLine() const
{
    return mCurrentLine;
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



QIODevice *AbstractRegionReader::device()
{
    return mDevice;
}


void AbstractRegionReader::setRegion(const Region &region)
{
    mRegion = region;
}

void AbstractRegionReader::setCurrentLine(qint64 line)
{
    mCurrentLine = line;
}

}}
