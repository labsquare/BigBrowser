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


private:
    QByteArray mSeq;
};

}}

#endif // SEQUENCE_H
