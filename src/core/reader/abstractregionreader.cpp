#include "abstractregionreader.h"

namespace big {

AbstractRegionReader::AbstractRegionReader(const QString& filename)
    :mFile(filename)
{

}

bool AbstractRegionReader::open(QIODevice::OpenMode mode)
{
    return mFile.open(mode);
}

void AbstractRegionReader::close()
{
    mFile.close();
}

QFile *AbstractRegionReader::device()
{
    return &mFile;
}

}
