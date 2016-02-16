#ifndef REGION_H
#define REGION_H
#include <QtCore>

namespace big {

class Region
{
public:
    Region();

    const QString& chrom() const;
    int pos() const;
    int length() const;

    void setChrom(const QString& chrom);
    void setPos(int pos);
    void setLength(int length);

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
