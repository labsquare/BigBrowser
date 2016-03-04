#include "gffreader.h"

namespace big {
namespace core {
GffReader::GffReader(const QString &filename)
    :AbstractRegionReader(filename)
{

}

bool GffReader::next()
{
    return false;
}

}}
