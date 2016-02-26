#ifndef REGION_H
#define REGION_H
#include <QtCore>

namespace big {

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
     * \param end: the ending position. Not include in the region.
     */
    Region(const QString& chromosom, int start, int end);
    /*!
     * \brief Region Constructor
     * \param expression: expression in format <chromosom>:<pos>-<end>: "chr4:1000-20000"
     */
    Region(const QString& expression);
    /*!
     * \brief chromosom
     * \return chromosome name
     */
    const QString& chromosom() const;
    /*!
     * \brief pos
     * \return the position. equivalent to start()
     */
    int pos() const;
    /*!
     * \brief length
     * \return the length of region.
     */
    int length() const;
    /*!
     * \brief start
     * \return the position start of region
     */
    int start() const;
    /*!
     * \brief end
     * \return the position end of region
     */
    int end() const;
    /*!
     * \brief setChromosom
     * \param chromosom
     */
    void setChromosom(const QString& chromosom);
    /*!
     * \brief setPos
     * \param pos
     */
    void setPos(int pos);
    /*!
     * \brief setLength
     * \param length
     */
    void setLength(int length);
    /*!
     * \brief setRange
     * \param start
     * \param end
     */
    void setRange(int start, int end);
    /*!
     * \brief addData
     * \param key
     * \param value
     *
     * \details Add extra data into internal dictionnary
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


private:
    QString mChrom;
    int mPos;
    int mLength;
    QHash<QString, QVariant> mDatas;

};
}

#endif // REGION_H
