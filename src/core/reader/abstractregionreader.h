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

    // Get next region. Use region() to get it
    virtual bool next() = 0;

    // Set Query. Get range from this query
    void setQuery(const QString& chromosom, int start, int end);
    void setQuery(const RegionQuery& query);

    // Get current region. Use next, to get the next one iteratively.
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
