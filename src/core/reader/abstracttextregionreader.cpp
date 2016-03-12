#include "abstracttextregionreader.h"
namespace big {
namespace core {

AbstractTextRegionReader::AbstractTextRegionReader(QIODevice *device)
    :AbstractRegionReader(device)
{
    mStream.setDevice(device);
}

AbstractTextRegionReader::AbstractTextRegionReader(const QString &filename)
    :AbstractRegionReader(filename)
{
    mStream.setDevice(device());

}

bool AbstractTextRegionReader::next()
{
    if (!device()->isReadable()){
        qDebug()<<Q_FUNC_INFO<<"device is not readable. Did you open it ? ";
        return false;
    }

    QString line = mStream.readLine();
    Region region = parseLine(line);
    if (!region.isNull())
        setCurrentRegion(region);
    else
        return false;

    if (mStream.atEnd())
        return false;

    return true;


}

}} // end namespace
