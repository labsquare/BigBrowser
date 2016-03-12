#include "gffreader.h"
#include "abstracttextregionreader.h"
namespace big {
namespace core {
GffReader::GffReader(const QString &filename)
    :AbstractTextRegionReader(filename)
{

}

Region GffReader::parseLine(const QString &line) const
{
 return Region();
}



}}
