#include "selection.h"
namespace big {
namespace core {
Selection::Selection()
    :mChromosom(),mStart(0), mEnd(0)
{

}

Selection::Selection(const QString &chromosom, quint64 start, quint64 end)
    :mChromosom(chromosom),mStart(start), mEnd(end)
{

}

QString Selection::chromosom() const
{
    return mChromosom;
}

void Selection::setChromosom(const QString &chromosom)
{
    mChromosom = chromosom;
}

quint64 Selection::start() const
{
    return mStart;
}

void Selection::setStart(const quint64 &start)
{
    mStart = start;
}

quint64 Selection::end() const
{
    return mEnd;
}

void Selection::setEnd(const quint64 &end)
{
    mEnd = end;
}

Region Selection::toRegion()
{
    Region region(mChromosom,mStart, mEnd);
    return region;

}

void Selection::fromRegion(const Region &region)
{
    setChromosom(region.chromosom());
    setStart(region.start());
    setEnd(region.end());
}

}} // end namespace
