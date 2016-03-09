#ifndef GENOM_H
#define GENOM_H
#include <QtCore>
#include "sequence.h"
#include "region.h"
#include "regionlist.h"
#include "cytobandreader.h"
#include "quazip.h"
#include "quazipfile.h"


namespace big {
namespace core {
/*!
 * \brief Describe a genom
 */
class Genom
{
public:

    Genom();
    Genom(QIODevice * device);
    Genom(const QString& filename);
    ~Genom();

    void load(QIODevice * device);
    void load(const QString& filename);


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

    QStringList chromosoms();

    /*!
     * \brief cytoBand
     * Return cytoband according chromosom name
     * \param chromosom
     * \return list of Region
     */
    const RegionList chromosomBand(const QString& chromosom) const;


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
     QString name() const;
     QString id() const;


    bool isValid();

    /*!
     * \brief hasIndex
     *
     * Check if faidx exists for the genom
     * \return True if it exists. Otherwise return false
     */
//    bool hasIndex();

    /*!
     * \brief hasCytoband
     * \return if cytoband file exists
     */
    bool hasCytoband();

//    /*!
//     * \brief createIndex
//     *
//     * Create the faidx for the genom.
//     *
//     * Please read this page, to understand the purpose of this methodes
//     * http://www.htslib.org/doc/faidx.html
//     * \todo Threading the process ?
//     */
//    bool createIndex();

protected:
    void loadCytoBand(QIODevice * device);
    void loadProperty(QIODevice * device);



private:

    // each chromosom have name and size
    QHash<QString, quint64> mChromosomsSize;
    QHash<QString, RegionList> mChromosomsBands;
    QHash<QString, QString> mProperties;
    QuaZip mZip;

    QIODevice * mDevice;





};
}}
#endif // GENOM_H
