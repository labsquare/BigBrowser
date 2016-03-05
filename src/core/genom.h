#ifndef GENOM_H
#define GENOM_H
#include <QtCore>
#include "sequence.h"
#include "region.h"
#include "cytobandreader.h"

namespace big {
namespace core {
/*!
 * \brief Describe a genom
 */
class Genom
{
public:
    /*!
     * \brief The FileType enum contains 3 kind of file to work with genom
     * GenomFile is the fasta file. hg19.fa
     * IndexFile is the fasta index file .  hg19.fa.fai
     * CytobandFile contains band regions. hg19.cytoBand
     */
    enum FileType {
        GenomFile    = 0x0000,
        IndexFile    = 0x0001,
        CytobandFile = 0x0002,
    };

    Genom(const QString& filename);


    /*!
     * \brief chromosomCount
     * \return how many chromosom are in the genom
     */
    int chromosomCount();

    /*!
     * \brief chromosomLength
     * \param chromosom
     * \return the length of chromosom
     */
    int chromosomLength(const QString& chromosom);

    /*!
     * \brief cytoBand
     * Return cytoband according chromosom name
     * \param chromosom
     * \return list of Region
     */
    RegionList cytoBand(const QString& chromosom);


    /*!
     * \brief sequence
     *
     * Warning : Genom should be indexed in faidx.
     * \see hasIndex
     * \param chromosom
     * \param pos
     * \param length
     * \return a dna sequence according param location
     */
    Sequence sequence(const QString& chromosom, quint64 pos, quint64 length);

    /*!
     * \brief name
     * \return the genom name
     */
    const QString& name() const;
    const QString& filename(FileType type = Genom::GenomFile) const;


    bool isValid();

    /*!
     * \brief hasIndex
     *
     * Check if faidx exists for the genom
     * \return True if it exists. Otherwise return false
     */
    bool hasIndex();

    /*!
     * \brief hasCytoband
     * \return if cytoband file exists
     */
    bool hasCytoband();

    /*!
     * \brief createIndex
     *
     * Create the faidx for the genom.
     *
     * Please read this page, to understand the purpose of this methodes
     * http://www.htslib.org/doc/faidx.html
     * \todo Threading the process ?
     */
    bool createIndex();

protected:
    void loadChromosoms();


private:
    QString mFilename;
    QString mIndexFilename;
    QString mCytobandFilename;
    QString mName;
    // each chromosom have name and size
    QHash<QByteArray, quint64> mChromosoms;




};
}}
#endif // GENOM_H
