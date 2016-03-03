#ifndef GENOM_H
#define GENOM_H
#include <QtCore>
#include "sequence.h"
namespace big {
namespace core {
/*!
 * \brief Describe a genom
 */
class Genom
{
public:
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
     * \brief sequence
     *
     * Warning : Genom should be indexed in faidx.
     * \see hasIndex
     * \param chromosom
     * \param pos
     * \param length
     * \return a dna sequence according param location
     */
    Sequence sequence(const QString& chromosom, qint64 pos, qint64 length);

    /*!
     * \brief name
     * \return the genom name
     */
    const QString& name() const;
    const QString& filename() const;

    bool isValid();

    /*!
     * \brief hasIndex
     *
     * Check if faidx exists for the genom
     * \return True if it exists. Otherwise return false
     */
    bool hasIndex();

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

    bool loadIndex();


private:
    QString mFilename;
    QString mName;




};
}}
#endif // GENOM_H
