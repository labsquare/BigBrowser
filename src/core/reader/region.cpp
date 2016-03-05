#include "region.h"
#include <QRegularExpression>
#include <QDebug>
namespace big {
namespace core {
Region::Region()
    :mPos(0),mLength(0)
{

}

Region::Region(const QString &chromosom, quint64 pos, quint64 length)
{
    setChromosom(chromosom);


}

const QString &Region::name() const
{
    if (mName.isEmpty())
        return mChrom;
    else
        return mName;
}

const QString &Region::chromosom() const
{
    return mChrom;
}

quint64 Region::pos() const
{
    return mPos;
}

quint64 Region::length() const
{
    return mLength;
}

quint64 Region::first() const
{
    return pos();
}

quint64 Region::last() const
{
    return pos() + length() - 1;
}

void Region::setRange(quint64 start, quint64 end)
{
    setPos(start);
    setLength(end - start);
}

void Region::setName(const QString &name)
{
    mName = name;
}

void Region::setChromosom(const QString &chromosom)
{
    mChrom = chromosom;
}

void Region::setPos(quint64 pos)
{
    mPos = pos;
}

void Region::setLength(quint64 length)
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

Region Region::fromBed(const QString &chrom, quint64 chromStart, quint64 chromEnd)
{
    Region region;
    region.setChromosom(chrom);
    region.setPos(chromStart);
    region.setLength(chromEnd - chromStart);
    return region;
}

Region Region::fromBed(const QString &expression)
{
    QRegularExpression re("(\\d+):(\\d+)-(\\d+)");
    QRegularExpressionMatch match = re.match(expression);
    Region region;

    if (match.isValid())
    {
        region.setChromosom(match.captured(1));
        region.setPos(match.captured(2).toInt());
        region.setLength(region.pos() - match.captured(3).toInt());
    }
    else {
        qDebug()<<Q_FUNC_INFO<<"bad expression";
    }

    return region;
}

}}
