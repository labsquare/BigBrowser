#include "vcfreader.h"
#include <QStringList>
namespace big {
namespace core {
VcfReader::VcfReader(const QString& filename)
    :AbstractTextRegionReader(filename)
{

}

Region VcfReader::parseLine(const QString &line) const
{
    // implement https://samtools.github.io/hts-specs/VCFv4.2.pdf
    if (line.startsWith("#"))
        return Region();

    QStringList items = line.split("\t");
    Region region;

    if (items.count()>=8)
    {
        region.setChromosom(items.at(0));
        region.setStart(items.at(1).toInt()+1);
        region.setEnd(region.start()+1);
        region.addData("ID", items.at(2));
        region.addData("REF", items.at(3));
        region.addData("ALT", items.at(4));
        region.addData("QUAL", items.at(5));
        region.addData("FILTER", items.at(6));
        region.addData("INFO", items.at(7));
    }

    return region;
}



}} // end namespace
