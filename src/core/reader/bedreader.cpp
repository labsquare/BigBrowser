#include "bedreader.h"

namespace big {
namespace core {

BedReader::BedReader(const QString &filename)
    :AbstractTextRegionReader(filename)
{


}

Region BedReader::parseLine(const QString &line) const
{

    return Region();
}




}}
