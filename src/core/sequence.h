#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QtCore>

namespace big {
    namespace core {

        /*!
         * \brief Contains DNA sequence in IUPAC Format
         */
	class Sequence
	{
    
	public:
	    Sequence(const QByteArray& seq);
	    Sequence();

	    void setSequence(const QByteArray& seq);

	    QString toString() const;

	    /*!
	     * \brief complement
	     * \return the complement sequence
	     */
	    Sequence complement() const;

	    /*!
	     * \brief reverseComplement
	     * \return the reverse complement sequence
	     */
	    Sequence reverseComplement() const;

	    /*!
	     * \brief transcribe
	     * \return the rna sequence from dna sequence
	     */
	    Sequence transcribe() const;

	    /*!
	     * \brief backTranscribe
	     * \return Return the dna sequence from rna sequence
	     */
	    Sequence backTranscribe() const;

	    /*!
	     * \brief fromFasta
	     *
	     * Create a sequence from fasta file
	     * \param filename
	     * \return
	     */
	    static Sequence fromFasta(const QString& filename);

	protected:

	    /*!
	     * \brief getComplement
	     *
	     * Return the complement of nucleotide.
	     *
	     * For Adenine return always Thymine no Uracil.
	     * If IUPAC alphabet is use in sequence we return the same letter.
	     * Case is keep
	     *
	     * If letter is not in IUPAC Alphabet behavior of function is 
	     * undefine
	     *
	     * \param nucleotide
	     * \return the complement of original nucleotide
	     */
	    char getComplement(char nuc);

	private:
	    QByteArray mSeq;
	    static char mComplement[120];
	};

	// Init of mComplement table
	mComplement['-'] = '-'; // gap
	mComplement['.'] = '.'; // gap
	mComplement['A'] = 'A'; // Adenine
	mComplement['B'] = 'B'; // C or G or T
	mComplement['C'] = 'G'; // Cytosine
	mComplement['D'] = 'D'; // A or G or T
	mComplement['G'] = 'C'; // Guanine
	mComplement['H'] = 'H'; // A or C or T
	mComplement['K'] = 'K'; // G or T
	mComplement['M'] = 'M'; // A or C
	mComplement['N'] = 'N'; // any base
	mComplement['R'] = 'R'; // A or G
	mComplement['S'] = 'S'; // G or C
	mComplement['T'] = 'A'; // Thymine
	mComplement['U'] = 'A'; // Uracil
	mComplement['V'] = 'V'; // A or C or G
	mComplement['W'] = 'W'; // A or T
	mComplement['Y'] = 'Y'; // C or G
	mComplement['a'] = 't'; // Adenine
	mComplement['b'] = 'b'; // C or G or T
	mComplement['c'] = 'g'; // Cytosine
	mComplement['d'] = 'd'; // A or G or T
	mComplement['g'] = 'c'; // Guanine
	mComplement['h'] = 'h'; // A or C or T
	mComplement['k'] = 'k'; // G or T
	mComplement['m'] = 'm'; // A or C
	mComplement['n'] = 'n'; // any base
	mComplement['r'] = 'r'; // A or G
	mComplement['s'] = 's'; // G or C
	mComplement['t'] = 'a'; // Thymine
	mComplement['u'] = 'a'; // Uracil
	mComplement['v'] = 'v'; // A or C or G
	mComplement['w'] = 'w'; // A or T
	mComplement['y'] = 'y'; // C or G
	
    } // end of namespace core
} // end of namespace big

#endif // SEQUENCE_H
