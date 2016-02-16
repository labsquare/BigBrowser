#include "region.h"
namespace big {

Region::Region()
    :mPos(0),mLength(0)
{

}

const QString &Region::chrom() const
{
    return mChrom;
}

int Region::pos() const
{
    return mPos;
}

int Region::length() const
{
    return mLength;
}

void Region::setPos(int pos)
{
    mPos = pos;
}

void Region::setLength(int length)
{
    mLength = length;
}

void Region::addData(const QString &key, const QVariant &value)
{
    mDatas.insert(key, value);
}

QVariant Region::data(const QString &key) const
{
    return mDatas.value(key);
}

void Region::clearData()
{

    mDatas.clear();
}

}
