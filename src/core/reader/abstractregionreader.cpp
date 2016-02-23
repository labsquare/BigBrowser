#include "abstractregionreader.h"

namespace big {

AbstractRegionReader::AbstractRegionReader(const QString& filename)
{

    mDevice = new QFile(filename);
    setQuery("",0,0);

}

AbstractRegionReader::AbstractRegionReader(QIODevice *device)
{
    mDevice = device;
    setQuery("",0,0);
}

void AbstractRegionReader::setQuery(const QString &chromosom, int start, int end)
{
    RegionQuery q;
    q.chromosom = chromosom;
    q.start = start;
    q.end = end;
    setQuery(q);
}

void AbstractRegionReader::setQuery(const RegionQuery &query)
{
    mQuery = query;
}

const Region &AbstractRegionReader::region()
{
    return  mRegion;
}

QIODevice *AbstractRegionReader::device()
{
    return mDevice;
}

const RegionQuery &AbstractRegionReader::query() const
{
    return mQuery;
}

void AbstractRegionReader::setRegion(const Region &region)
{
    mRegion = region;
}

}
