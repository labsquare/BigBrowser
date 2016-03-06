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

private:
    QByteArray mSeq;
    static QHash<char,char> complementTable ;
    //	    static char mComplement[120];
};

// Init of mComplement table


} // end of namespace core
} // end of namespace big

#endif // SEQUENCE_H
