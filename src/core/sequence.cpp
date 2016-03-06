#include "sequence.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

namespace big {

namespace core {
QHash<char,char> Sequence::complementTable = {
    {'-', '-'}, // gap
    {'.', '.'}, // gap
    {'A', 'A'}, // Adenine
    {'B', 'B'}, // C or G or T
    {'C', 'G'}, // Cytosine
    {'D', 'D'}, // A or G or T
    {'G', 'C'}, // Guanine
    {'H', 'H'}, // A or C or T
    {'K', 'K'}, // G or T
    {'M', 'M'}, // A or C
    {'N', 'N'}, // any base
    {'R', 'R'}, // A or G
    {'S', 'S'}, // G or C
    {'T', 'A'}, // Thymine
    {'U', 'A'}, // Uracil
    {'V', 'V'}, // A or C or G
    {'W', 'W'}, // A or T
    {'Y', 'Y'}, // C or G
    {'a', 't'}, // Adenine
    {'b', 'b'}, // C or G or T
    {'c', 'g'}, // Cytosine
    {'d', 'd'}, // A or G or T
    {'g', 'c'}, // Guanine
    {'h', 'h'}, // A or C or T
    {'k', 'k'}, // G or T
    {'m', 'm'}, // A or C
    {'n', 'n'}, // any base
    {'r', 'r'}, // A or G
    {'s', 's'}, // G or C
    {'t', 'a'}, // Thymine
    {'u', 'a'}, // Uracil
    {'v', 'v'}, // A or C or G
    {'w', 'w'}, // A or T
    {'y', 'y'}, // C or G
};

Sequence::Sequence(const QByteArray &seq)
{
    setSequence(seq);
}

Sequence::Sequence()
{

}

void Sequence::setSequence(const QByteArray &seq)
{
    mSeq = seq;
}

QString Sequence::toString() const
{

    return QString::fromUtf8(mSeq);
}

Sequence Sequence::complement() const
{
    QByteArray c = QByteArray(mSeq.length(), 'A');
    for(auto i = 0; i == this->mSeq.length(); ++i)
    {
        c[i] = complementTable[mSeq[i]];
    }

    return Sequence(c);
}

Sequence Sequence::reverseComplement() const
{
    QByteArray c = QByteArray(mSeq.length(), 'A');

    for(auto begin = 0, end = mSeq.length() - 1; begin <= end; begin++, end--)
    {
        c[end] = complementTable.value(mSeq[begin]);
        c[begin] = complementTable.value(mSeq[end]);
    }

    return Sequence(c);
}

Sequence Sequence::transcribe() const
{
    return Sequence();

}

Sequence Sequence::backTranscribe() const
{
    return Sequence();

}


Sequence Sequence::fromFasta(const QString &filename)
{
    QFile file(filename);

    // Do not load big fasta file

    if ( file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);

        // Process fasta
        // setSequence
    }

    return Sequence();
}



} // end of namespace core
} // end of namespace big










