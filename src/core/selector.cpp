#include "selector.h"
#include <QDebug>
#include <QRegularExpression>
namespace big {
namespace core {

Selector::Selector(QObject * parent)
    :QObject(parent),mChromosom(), mStart(0), mEnd(0)
{

}

Selector::Selector(const QString &chromosom, quint64 start, quint64 end, QObject *parent)
    :QObject(parent), mChromosom(chromosom), mStart(start), mEnd(end)
{

}

QString Selector::toString() const
{
    return QString("%1:%2-%3").arg(mChromosom).arg(mStart).arg(mEnd);
}

void Selector::setSelection(const QString &pattern)
{
    // chr3:10-2324234
    QRegularExpression expression("(chr\\w):(\\d+)-(\\d+)");

    QRegularExpressionMatch match = expression.match(pattern);
    if (match.hasMatch())
    {
        QString chromosom = match.captured(1);
        quint64 start     = match.captured(2).toInt();
        quint64 end       = match.captured(3).toInt();
        setSelection(chromosom, start, end);
        return;
    }

    // chr3 only
    expression.setPattern("(chr\\w)");
    match = expression.match(pattern);
    if (match.hasMatch())
    {
        QString chromosom = match.captured(1);
        setSelection(chromosom, 0, 0);

        return;
    }
}


quint64 Selector::length() const
{
    return end()-start();

}

QString Selector::chromosom() const
{
    return mChromosom;
}

void Selector::setChromosom(const QString &chromosom)
{
    mChromosom = chromosom;
    emit changed();
}

quint64 Selector::start() const
{
    return mStart;
}

void Selector::setStart(const quint64 &pos)
{
    mStart = pos;
    emit changed();
}

quint64 Selector::end() const
{
    return mEnd;
}

void Selector::setEnd(const quint64 &end)
{
    mEnd = end;
    emit changed();
}

void Selector::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    mChromosom = chromosom;
    mStart     = start;
    mEnd       = end;
    emit changed();

}

void Selector::translate(qint64 baseCount)
{
    mStart += baseCount;
    mEnd   += baseCount;
    emit changed();

}

void Selector::scale(qint64 baseCount)
{
    mStart += baseCount;
    mEnd   -= baseCount;
    emit changed();
}



quint64 Selector::middle() const
{
    quint64 m = length()/2;
    return start() + m ;
}

void Selector::operator+=(qint64 baseCount)
{
    translate(baseCount);
}

void Selector::operator*=(qint64 baseCount)
{
    scale(baseCount);
}

bool Selector::isValid()
{
    // Need to check according genom ...

    return mChromosom.isEmpty();


}





}}
