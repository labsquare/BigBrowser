#ifndef ABSTRACTREGIONREADER_H
#define ABSTRACTREGIONREADER_H
#include <QObject>
#include <QFile>
#include "region.h"
namespace big {
class AbstractRegionReader
{

public:
    AbstractRegionReader(const QString& filename);

    virtual Region region(int row) = 0;
    virtual int count() = 0;

    bool open(QIODevice::OpenMode mode);
    void close();

    QFile * device();




private:
    QFile mFile;




};
}


#endif // ABSTRACTREGIONREADER_H
