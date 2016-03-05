#ifndef SECTION_H
#define SECTION_H
#include <QtCore>

namespace big {
namespace core {


class Section
{
public:
    Section();
    Section(const QString& chromosom, qint64 start, qint64 end);

    /*!
     * \brief length
     * \return the length of the section
     */
    qint64 length() const;


    /*!
     * \brief chromosom
     * \return the chromosom of the section
     */
    QString chromosom() const;
    void setChromosom(const QString &chromosom);

    /*!
     * \brief start
     * \return position of the first base in sequence bed format ( 0 - n  )
     */
    qint64 start() const;
    void setStart(const qint64 &start);

    /*!
     * \brief end
     * \return position of the last-1 base in sequence bed format ( 0 - n  )
     */
    qint64 end() const;
    void setEnd(const qint64 &end);

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

    /*!
     * \brief middle
     * \return the middle position. If length() is an odds, return the position of the left side
     */
    qint64 middle() const;

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

    bool isValid();

private:
    QString mChromosom;
    qint64 mStart;
    qint64 mEnd;
};


}} // end namespace

#endif // SECTION_H
