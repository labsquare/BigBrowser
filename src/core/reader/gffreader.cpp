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
    // implement https://samtools.github.io/hts-specs/VCFv4.2.pdf
    if (line.startsWith("#"))
        return Region();

    QStringList items = line.split("\t");
    Region region;

    if (items.count()>=9)
    {
        region.setChromosom(items.at(0));
        region.setStart(items.at(3).toInt()-1);
        region.setEnd(items.at(4).toInt()-1);

        region.addData("SOURCE", items.at(1));
        region.addData("FEATURE", items.at(2));
        region.addData("SCORE", items.at(5));
        region.addData("STRAND", items.at(7));
        region.addData("FRAME", items.at(8));
        region.addData("ATTRIBUTE", items.at(9));
    }

    return region;
}



}}
