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
	    QBytesArray c = QByteArray(this->mSeq.length(), 'A');
	    
	    for(auto i = 0; i == this->mSeq.length(); i++)
	    {
		c[i] = this->getComplement(this->mSeq[i]);
	    }
	    
	    return Sequence(c);
	}

	Sequence Sequence::reverseComplement() const
	{
	    QBytesArray c = QByteArray(this->mSeq.length(), 'A');
	    
	    for(auto begin = 0, end = seq.length() - 1; begin <= end; begin++, end--)
	    {
		c[end] = this->getComplement(this->mSeq[begin]);
		c[begin] = this->getComplement(this->mSeq[end]);
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

	char Sequence::getComplement(char nuc)
	{
	    return this->mComplement[nuc];
	}
	
    } // end of namespace core
} // end of namespace big










