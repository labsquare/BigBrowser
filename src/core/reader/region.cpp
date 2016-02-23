#include "region.h"
#include <QRegularExpression>
#include <QDebug>
namespace big {

Region::Region()
    :mPos(0),mLength(0)
{

}

Region::Region(const QString &chromosom, int start, int end)
{
    setChromosom(chromosom);
    setRange(start, end);
}

Region::Region(const QString &expression)
{
    QRegularExpression re("(\\d+):(\\d+)-(\\d+)");
    QRegularExpressionMatch match = re.match(expression);

    if (match.isValid())
    {
        setChromosom(match.captured(1));
        setRange(match.captured(2).toInt(),  match.captured(3).toInt());
    }
    else {
        qDebug()<<Q_FUNC_INFO<<"bad expression";
    }
}

const QString &Region::chromosom() const
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

int Region::start() const
{
    return pos();
}

int Region::end() const
{
    return pos() + length();
}

void Region::setChromosom(const QString &chromosom)
{
    mChrom = chromosom;
}

void Region::setPos(int pos)
{
    mPos = pos;
}

void Region::setLength(int length)
{
    mLength = length;
}

void Region::setRange(int start, int end)
{
    // Correct if order are wrong ...
    int s = qMin(start, end);
    int e = qMax(start,end);

    setPos(s);
    setLength(e-s);
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
