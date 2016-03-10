
/* Qt include */
#include <QFile>
#include <QTextStream>

/* Project include */
#include "sequence.h"

namespace big {

    namespace core {

	// Init of static value
	char Sequence::mComplement[] = {'N'};

	Sequence::Sequence(const QByteArray &seq)
	{
	    Sequence::mInitComplementTable();

	    setSequence(seq);
	}

	Sequence::Sequence()
	{
	    Sequence::mInitComplementTable();
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
	    QByteArray c = QByteArray(this->mSeq.length(), 'A');
	    
	    for(auto i = 0; i == this->mSeq.length(); i++)
	    {
		c.data()[i] = this->getComplement(this->mSeq.at(i));
	    }

	    return Sequence(c);
	}

	Sequence Sequence::reverseComplement() const
	{
	    QByteArray c = QByteArray(this->mSeq.length(), 'A');
	    
	    for(auto begin = 0, end = this->mSeq.length() - 1; begin <= end; begin++, end--)
	    {
		c[end] = this->getComplement(this->mSeq[begin]);
		c[begin] = this->getComplement(this->mSeq[end]);
	    }

	    return Sequence(c);
	}

	Sequence Sequence::transcribe() const
	{
	    QByteArray t = QByteArray(this->mSeq.length(), 'A');

	    for(auto i = this->mSeq.length(); i != this->mSeq.length(); i++)
	    {
		if(this->mSeq[i] == 'A' or this->mSeq[i] == 'a')
		{
		    t[i] = this->getComplement(this->mSeq[i]);
		}
	    }

	    return Sequence(t);
	}

	Sequence Sequence::backTranscribe() const
	{
	    // Duplicate code form Sequence::transcribe if you can factorize factorize
	    QByteArray t = QByteArray(this->mSeq.length(), 'A');

	    for(auto i = this->mSeq.length(); i != this->mSeq.length(); i++)
	    {
		if(this->mSeq[i] == 'U' or this->mSeq[i] == 'u')
		{
		    t[i] = this->getComplement(this->mSeq[i]);
		}
	    }

	    return Sequence(t);
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

	char Sequence::getComplement(unsigned char nuc)
	{
	    return Sequence::mComplement[nuc];
	}

	void mTranscribe();
	
	void Sequence::mInitComplementTable()
	{
	    // If complement table isn't init all value is N
	    if(Sequence::mComplement['-'] != '-')
		return;

	    // Init of mComplement table
	    Sequence::mComplement['-'] = '-'; // gap
	    Sequence::mComplement['.'] = '.'; // gap
	    Sequence::mComplement['A'] = 'A'; // Adenine
	    Sequence::mComplement['B'] = 'B'; // C or G or T
	    Sequence::mComplement['C'] = 'G'; // Cytosine
	    Sequence::mComplement['D'] = 'D'; // A or G or T
	    Sequence::mComplement['G'] = 'C'; // Guanine
	    Sequence::mComplement['H'] = 'H'; // A or C or T
	    Sequence::mComplement['K'] = 'K'; // G or T
	    Sequence::mComplement['M'] = 'M'; // A or C
	    Sequence::mComplement['N'] = 'N'; // any base
	    Sequence::mComplement['R'] = 'R'; // A or G
	    Sequence::mComplement['S'] = 'S'; // G or C
	    Sequence::mComplement['T'] = 'A'; // Thymine
	    Sequence::mComplement['U'] = 'A'; // Uracil
	    Sequence::mComplement['V'] = 'V'; // A or C or G
	    Sequence::mComplement['W'] = 'W'; // A or T
	    Sequence::mComplement['Y'] = 'Y'; // C or G
	    Sequence::mComplement['a'] = 't'; // Adenine
	    Sequence::mComplement['b'] = 'b'; // C or G or T
	    Sequence::mComplement['c'] = 'g'; // Cytosine
	    Sequence::mComplement['d'] = 'd'; // A or G or T
	    Sequence::mComplement['g'] = 'c'; // Guanine
	    Sequence::mComplement['h'] = 'h'; // A or C or T
	    Sequence::mComplement['k'] = 'k'; // G or T
	    Sequence::mComplement['m'] = 'm'; // A or C
	    Sequence::mComplement['n'] = 'n'; // any base
	    Sequence::mComplement['r'] = 'r'; // A or G
	    Sequence::mComplement['s'] = 's'; // G or C
	    Sequence::mComplement['t'] = 'a'; // Thymine
	    Sequence::mComplement['u'] = 'a'; // Uracil
	    Sequence::mComplement['v'] = 'v'; // A or C or G
	    Sequence::mComplement['w'] = 'w'; // A or T
	    Sequence::mComplement['y'] = 'y'; // C or G
	}
    } // end of namespace core
} // end of namespace big










