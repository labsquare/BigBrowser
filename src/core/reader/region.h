#ifndef REGION_H
#define REGION_H
#include <QtCore>

namespace big {
namespace core {
/*! \class Region
 * \brief Describe a region of dna delimited by chromosom:pos-length
 *
 */

class Region
{
public:
    Region();

    /*!
     * \brief Region Constructor.
     *
     * Create a region in genom reference.
     * For exemple, the first 100 bases of a chromosome are start=0 end=100, and based numbered 0 to 99
     * \param chromosom: chromosom name. eg: "chr5"
     * \param start: position start in 0 based
     * \param length: the length of region
     */
    Region(const QString& chromosom, qint64 pos, qint64 length);
    /*!
     * \brief Region Constructor
     * \param expression: expression in format <chromosom>:<pos>-<end>: "chr4:1000-20000"
     */
    Region(const QString& expression);


    const QString& name() const;


    /*!
     * \brief chromosom
     * \return chromosome name
     */
    const QString& chromosom() const;
    /*!
     * \brief pos
     * \return the position. equivalent to start()
     */
    qint64 pos() const;
    /*!
     * \brief length
     * \return the length of region.
     */
    qint64 length() const;
    /*!
     * \brief start
     * \return the position start of region
     */
    qint64 first() const;
    /*!
     * \brief end
     * \return the position end of region
     */
    qint64 last() const;

    void setRange(qint64 start, qint64 end);

    void setName(const QString& name);

    /*!
     * \brief setChromosom
     * \param chromosom
     */
    void setChromosom(const QString& chromosom);
    /*!
     * \brief setPos
     * \param pos
     */
    void setPos(qint64 pos);
    /*!
     * \brief setLength
     * \param length
     */
    void setLength(qint64 length);
    /*!
     * \brief setRange
     * \param start
     * \param end
     */

    void addData(const QString& key, const QVariant& value);
    /*!
     * \brief data
     * \param key
     * \return extra data value from key
     */
    QVariant data(const QString& key) const;
    /*!
     * \brief clearData
     *
     * Clear all extra data
     */

    void clearData();


    static Region fromBed(const QString& chrom, qint64 chromStart, qint64 chromEnd);
    static Region fromBed(const QString& expression);


private:
    QString mChrom;
    QString mName;
    qint64 mPos;
    qint64 mLength;
    QHash<QString, QVariant> mDatas;

};
}}

#endif // REGION_H
