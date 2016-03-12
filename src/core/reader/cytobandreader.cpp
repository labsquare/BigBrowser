#include "cytobandreader.h"

namespace big {
namespace core {
CytobandReader::CytobandReader(const QString &filename):
    AbstractTextRegionReader(filename)
{
}
CytobandReader::CytobandReader(QIODevice * device):
    AbstractTextRegionReader(device)
{
}

Region CytobandReader::parseLine(const QString &line) const
{
    QStringList items = line.split("\t");
    Region region;
    if (items.count() == 5){
        region.setChromosom(items.at(0));
        region.setStart(items.at(1).toInt());
        region.setEnd(items.at(2).toInt());
        region.setName(items.at(3));
        region.addData("stain",items.at(4));
    }

    return region;
}





}}
