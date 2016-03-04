#include "bedreader.h"

namespace big {
namespace core {

BedReader::BedReader(const QString &filename)
    :AbstractRegionReader(filename)
{


}

bool BedReader::next()
{
    return false;
}


}}
