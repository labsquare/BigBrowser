#include "sequence.h"
#include <QFile>
#include <QTextStream>
namespace big {
Sequence::Sequence(const QByteArray &seq)
{

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

       if ( file.open(QIODevice::ReadOnly))
       {
            QTextStream stream(&file);

            // Process fasta
       }

       // Return Sequence
}

}
