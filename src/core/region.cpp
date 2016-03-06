#include "region.h"
#include <QRegularExpression>
#include <QDebug>
namespace big {
namespace core {
Region::Region()
    :mStart(0),mEnd(0)
{

}

Region::Region(const QString &chromosom, quint64 start, quint64 end)
    :mChrom(chromosom),mStart(start),mEnd(end)
{
    setRegion(chromosom,start,end);
}

const QString &Region::name() const
{
    if (mName.isEmpty())
        return chromosom();
    else
        return mName;
}

const QString &Region::chromosom() const
{
    return mChrom;
}

quint64 Region::length() const
{
    return mEnd - mStart;
}

quint64 Region::start() const
{
    return mStart;
}

void Region::setStart(const quint64 &start)
{
    mStart = start;
}

quint64 Region::end() const
{
    return mEnd;
}

void Region::setEnd(const quint64 &end)
{
    mEnd = end;
}

void Region::setRegion(const QString &chromosom, quint64 start, quint64 end)
{
    setChromosom(chromosom);
    setStart(start);
    setEnd(end);
}

void Region::setName(const QString &name)
{
    mName = name;
}

void Region::setChromosom(const QString &chromosom)
{
    mChrom = chromosom;
}

void Region::setLength(quint64 length)
{
    setEnd(start() + length);
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

void Region::operator+=(qint64 baseCount)
{
    translate(baseCount);
}

void Region::operator*=(qint64 baseCount)
{
    scale(baseCount);
}

//bool Region::isValid(Genom *genom)
//{
//    if (!genom)
//        return false;

//    return genom->chromosoms().contains(chromosom())
//            && (start() >= 0)
//            && (end() < genom->chromosomLength(chromosom()));

//}

void Region::translate(qint64 baseCount)
{
    setStart(start() + baseCount);
    setEnd(end()     + baseCount);
}

void Region::scale(qint64 baseCount)
{
    setStart(start() + baseCount);
    setEnd(end()     - baseCount);
}

QString Region::toString() const
{
    return QString("%1:%2-%3").arg(chromosom()).arg(start()).arg(end());
}

}}
