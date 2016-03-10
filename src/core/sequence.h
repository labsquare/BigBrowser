#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QtCore>

#include "revcomp.h"

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

	private:

	    QByteArray mSeq;
	};
    } // end of namespace core
} // end of namespace big

#endif // SEQUENCE_H
