#include "cytobandreader.h"

namespace big {
namespace core {
CytobandReader::CytobandReader(const QString &filename):
    AbstractRegionReader(filename)
{

    mStream.setDevice(device());
}
CytobandReader::CytobandReader(QIODevice * device):
    AbstractRegionReader(device)
{
    mStream.setDevice(device);
}

bool CytobandReader::next()
{

    if (!device()->isOpen()){
        qDebug()<<Q_FUNC_INFO<<"device is not open";
        return false;
    }


    QStringList items = mStream.readLine().split("\t");
    if (items.size() == 5){
        Region region;
        region.setChromosom(items.at(0));
        region.setStart(items.at(1).toInt());
        region.setEnd(items.at(2).toInt());
        region.setName(items.at(3));
        region.addData("stain",items.at(4));


        setRegion(region);
        setCurrentLine(currentLine()+1);
    }

    if (mStream.atEnd())
        return false;


    return true;

}



}}
