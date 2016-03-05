#include "section.h"
namespace big {
namespace core {

Section::Section(QObject * parent)
    :QObject(parent),mChromosom(), mStart(0), mEnd(0)
{

}

Section::Section(const QString &chromosom, quint64 pos, quint64 end, QObject * parent)
    :QObject(parent),mChromosom(chromosom), mStart(pos), mEnd(pos)
{



}

quint64 Section::length() const
{
    return end()-start();

}

QString Section::chromosom() const
{
    return mChromosom;
}

void Section::setChromosom(const QString &chromosom)
{
    mChromosom = chromosom;
    emit changed();
}

quint64 Section::start() const
{
    return mStart;
}

void Section::setStart(const quint64 &pos)
{
    mStart = pos;
    emit changed();
}

quint64 Section::end() const
{
    return mEnd;
}

void Section::setEnd(const quint64 &end)
{
    mEnd = end;
    emit changed();
}

void Section::translate(qint64 baseCount)
{
    mStart += baseCount;
    mEnd += baseCount;
    emit changed();

}

void Section::scale(qint64 baseCount)
{
    mStart += baseCount;
    mEnd -= baseCount;
    emit changed();
}

quint64 Section::middle() const
{
    quint64 m = length()/2;
    return start() + m ;
}

void Section::operator+=(qint64 baseCount)
{
    translate(baseCount);
}

void Section::operator*=(qint64 baseCount)
{
    scale(baseCount);
}

bool Section::isValid()
{
    // Need to check according genom ...

    return mChromosom.isEmpty();


}





}}
