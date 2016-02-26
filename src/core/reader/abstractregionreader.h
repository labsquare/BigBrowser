#ifndef ABSTRACTREGIONREADER_H
#define ABSTRACTREGIONREADER_H
#include <QObject>
#include <QFile>
#include "region.h"
namespace big {

class RegionQuery {
public:
    QString chromosom;
    int start;
    int end;
};

class AbstractRegionReader
{

public:
    AbstractRegionReader(const QString& filename);
    AbstractRegionReader(QIODevice * device);

    virtual bool next() = 0;

    void setQuery(const QString& chromosom, int start, int end);
    void setQuery(const RegionQuery& query);

   const Region& region();


protected:
    QIODevice * device();
    const RegionQuery& query() const;
    void setRegion(const Region& region);





private:
    QIODevice * mDevice;
    Region mRegion;
    RegionQuery mQuery;



};
}


#endif // ABSTRACTREGIONREADER_H
