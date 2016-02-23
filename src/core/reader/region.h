#ifndef REGION_H
#define REGION_H
#include <QtCore>

namespace big {

/*! \class Region
 * \brief Describe an a region of dna delimited by chromosom:pos-length
 *
 */

class Region
{
public:
    Region();
    Region(const QString& chromosom, int start, int end);
    // Create Region fom string expression : chr4:1000-20000
    Region(const QString& expression);

    const QString& chromosom() const;
    int pos() const;
    int length() const;
    int start() const;
    int end() const;

    void setChromosom(const QString& chromosom);
    void setPos(int pos);
    void setLength(int length);
    void setRange(int start, int end);
    void addData(const QString& key, const QVariant& value);
    QVariant data(const QString& key) const;
    void clearData();


private:
    QString mChrom;
    int mPos;
    int mLength;
    QHash<QString, QVariant> mDatas;

};
}

#endif // REGION_H
