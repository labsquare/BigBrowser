#include "abstracttextregionreader.h"
namespace big {
namespace core {

AbstractTextRegionReader::AbstractTextRegionReader(QIODevice *device)
    :AbstractRegionReader(device)
{
    mStream.setDevice(device);
}

AbstractTextRegionReader::AbstractTextRegionReader(const QString &filename)
    :AbstractRegionReader(new QFile(filename))
{
    //    QFileInfo info(filename);
    //    AbstractRegionReader::AbstractRegionReader(new QFile(filename));

    mStream.setDevice(device());

}

bool AbstractTextRegionReader::next()
{
    if (!device()->isReadable()){
        qDebug()<<Q_FUNC_INFO<<"device is not readable. Did you open it ? ";
        return false;
    }

    Region region;
    while (region.isNull()){
        QString line = mStream.readLine();
        region = parseLine(line);

        if (mStream.atEnd())
            return false;


    }

    setCurrentRegion(region);
    return true;


}

}} // end namespace
