#include "sequence.h"
#include <QFile>
#include <QTextStream>
namespace big {
namespace core {
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

}

Sequence Sequence::reverseComplement() const
{

}

Sequence Sequence::transcribe() const
{

}

Sequence Sequence::backTranscribe() const
{

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

    // Return Sequence
}

}}
