#ifndef SECTION_H
#define SECTION_H
#include <QtCore>
#include <QObject>
namespace big {
namespace core {


class Section: public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 start READ start WRITE setStart NOTIFY changed)
    Q_PROPERTY(qint64 end READ end WRITE setEnd NOTIFY changed)

public:
    Section(QObject * parent = 0);
    Section(const QString& chromosom, qint64 start, qint64 end, QObject * parent = 0);

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

    /*!
     * \brief start
     * \return position of the first base in sequence bed format ( 0 - n  )
     */
    qint64 start() const;

    /*!
     * \brief end
     * \return position of the last-1 base in sequence bed format ( 0 - n  )
     */
    qint64 end() const;



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

public Q_SLOTS:
    void setChromosom(const QString &chromosom);
    void setStart(const qint64 &start);
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



Q_SIGNALS:
    void changed();


private:
    QString mChromosom;
    qint64 mStart;
    qint64 mEnd;
};


}} // end namespace

#endif // SECTION_H
