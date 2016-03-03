#include "region.h"
#include <QRegularExpression>
#include <QDebug>
namespace big {
namespace core {
Region::Region()
    :mPos(0),mLength(0)
{

}

Region::Region(const QString &chromosom, qint64 pos, qint64 length)
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

qint64 Region::pos() const
{
    return mPos;
}

qint64 Region::length() const
{
    return mLength;
}

qint64 Region::first() const
{
    return pos();
}

qint64 Region::last() const
{
    return pos() + length() - 1;
}

void Region::setRange(qint64 start, qint64 end)
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

void Region::setPos(qint64 pos)
{
    mPos = pos;
}

void Region::setLength(qint64 length)
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

Region Region::fromBed(const QString &chrom, qint64 chromStart, qint64 chromEnd)
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
