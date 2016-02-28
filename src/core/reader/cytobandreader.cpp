#include "cytobandreader.h"

namespace big {
namespace core {
CytobandReader::CytobandReader(const QString &filename):
    AbstractRegionReader(filename)
{


    mStream.setDevice(device());


}

bool CytobandReader::next()
{

    if (!device()->isOpen())
        device()->open(QIODevice::ReadOnly);




    QStringList items = mStream.readLine().split("\t");

    Region region;
    region.setChromosom(items.at(0));
    region.setPos(items.at(1).toInt());
    region.setLength(items.at(2).toInt() - region.pos());
    region.setName(items.at(3));
    region.addData("stain",items.at(4));
    region.addData("stain",items.at(4));

    setRegion(region);
    setCurrentLine(currentLine()+1);

    if (mStream.atEnd()){
        device()->close();
        return false;
    }

    return true;

}



}}
