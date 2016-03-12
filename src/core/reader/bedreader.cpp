#include "bedreader.h"

namespace big {
namespace core {

BedReader::BedReader(const QString &filename)
    :AbstractTextRegionReader(filename)
{


}

Region BedReader::parseLine(const QString &line) const
{

    // implement https://samtools.github.io/hts-specs/VCFv4.2.pdf
    if (line.startsWith("#"))
        return Region();

    QStringList items = line.split("\t");
    Region region;

    if (items.count()>=3)
    {
        region.setChromosom(items.at(0));
        region.setStart(items.at(1).toInt()-1);
        region.setEnd(items.at(2).toInt()-1);
    }

    return region;
}




}}
