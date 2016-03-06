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
    Region(const QString& chromosom, quint64 start, quint64 end);
    /*!
     * \brief Region Constructor
     * \param expression: expression in format <chromosom>:<pos>-<end>: "chr4:1000-20000"
     */
    Region(const QString& pattern);

    void setRegion(const QString& chromosom,quint64 start, quint64 end);
    void setRegion(const QString& patern);


    const QString& name() const;
    void setName(const QString& name);

    /*!
     * \brief chromosom
     * \return chromosome name
     */
    const QString& chromosom() const;
    /*!
     * \brief setChromosom
     * \param chromosom
     */
    void setChromosom(const QString& chromosom);

    quint64 length() const;
    /*!
     * \brief start
     * \return the position start of region
     */
    quint64 start() const;
    void setStart(const quint64 &start);
      /*!
     * \brief end
     * \return the position end of region
     */
    quint64 end() const;
    void setEnd(const quint64 &end);
    /*!
     * \brief middle
     * \return the middle position. If length() is an odds, return the position of the left side
     */
    quint64 middle() const;



    /*!
     * \brief setLength
     * \param length
     */
    void setLength(quint64 length);
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
    /*!
     * \brief operator +=
     * shortcut for translate methods
     * \param baseCount
     */
    void operator+=(qint64 baseCount);

    /*!
     * \brief operator *=
     * shortcut for scale method
     * \param baseCount
     */
    void operator*=(qint64 baseCount);

//    bool isValid(Genom *genom);

    /*!
     * \brief translate
     * Translate the section of basecount. Could be negatif or positif
     * \param baseCount
     */
    void translate(qint64 baseCount);

    /*!
     * \brief scale
     * Scale or zoom the section. Add baseCount from each side of the section
     * \param baseCount
     */
    void scale(qint64 baseCount);

    QString toString() const;




private:
    QString mChrom;
    quint64 mStart;
    quint64 mEnd;
    QString mName;
    QHash<QString, QVariant> mDatas;

};
}}

#endif // REGION_H
