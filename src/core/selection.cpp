#include "selection.h"
namespace big {
namespace core {

Selection::Selection(QObject * parent)
    :QObject(parent),mChromosom(), mStart(0), mEnd(0)
{

}

Selection::Selection(const QString &chromosom, quint64 pos, quint64 end, QObject * parent)
    :QObject(parent),mChromosom(chromosom), mStart(pos), mEnd(pos)
{



}

quint64 Selection::length() const
{
    return end()-start();

}

QString Selection::chromosom() const
{
    return mChromosom;
}

void Selection::setChromosom(const QString &chromosom)
{
    mChromosom = chromosom;
    emit changed();
}

quint64 Selection::start() const
{
    return mStart;
}

void Selection::setStart(const quint64 &pos)
{
    mStart = pos;
    emit changed();
}

quint64 Selection::end() const
{
    return mEnd;
}

void Selection::setEnd(const quint64 &end)
{
    mEnd = end;
    emit changed();
}

void Selection::translate(qint64 baseCount)
{
    mStart += baseCount;
    mEnd += baseCount;
    emit changed();

}

void Selection::scale(qint64 baseCount)
{
    mStart += baseCount;
    mEnd -= baseCount;
    emit changed();
}

quint64 Selection::middle() const
{
    quint64 m = length()/2;
    return start() + m ;
}

void Selection::operator+=(qint64 baseCount)
{
    translate(baseCount);
}

void Selection::operator*=(qint64 baseCount)
{
    scale(baseCount);
}

bool Selection::isValid()
{
    // Need to check according genom ...

    return mChromosom.isEmpty();


}





}}
