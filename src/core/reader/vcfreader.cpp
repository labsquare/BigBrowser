#include "vcfreader.h"
namespace big {
namespace core {
VcfReader::VcfReader(const QString& filename)
    :AbstractRegionReader(filename)
{

}

bool VcfReader::next()
{
 return false;
}

}} // end namespace
