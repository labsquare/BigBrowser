#include "abstractregionreader.h"

namespace big {



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
    mDevice->seek(0);
}

const Region &AbstractRegionReader::region() const
{
    return  mRegion;
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

}
