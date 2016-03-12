#include "vcfreader.h"
namespace big {
namespace core {
VcfReader::VcfReader(const QString& filename)
    :AbstractTextRegionReader(filename)
{

}

Region VcfReader::parseLine(const QString &line) const
{
 return Region();
}



}} // end namespace
