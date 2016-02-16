#include "bedreader.h"
#include <QDebug>
namespace big {



BedReader::BedReader(const QString &filename)
    :AbstractRegionReader(filename)
{

    mStream.setDevice(device());

}

Region BedReader::region(int row)
{



}

int BedReader::count()
{

}


}
