#ifndef ABSTRACTREGIONREADER_H
#define ABSTRACTREGIONREADER_H
#include <QObject>
#include <QIODevice>
#include "quazipfile.h"
#include "region.h"
#include "regionlist.h"
namespace big {
namespace core {

/*!
 * \brief Base class of all file Region Reader
 */
class AbstractRegionReader
{

public:
    AbstractRegionReader(QIODevice * device);
    AbstractRegionReader(const QString& filename);

    bool open(QIODevice::OpenMode mode = QIODevice::ReadOnly);

     /*!
     * \brief reset
     *
     * Reset current internal state to 0.
     */
    virtual void reset();
    /*!
     * \brief next
     *
     * iter to the next line and set the new region
     * \return True if success. If the end of file is reach , return false
     */
    virtual bool next() = 0;



    /*!
    * \brief region
    * \return current Region
    */
   const Region &region();

   /*!
    * \brief regions
    *
    * Load all regions into a RegionList.
    * !!WARNING!! Do not use this methods for large file. This load all region into memory
    * \return a list of all region
    */
   RegionList regions();







protected:
    QIODevice * device();
    void setCurrentRegion(const Region& region);

private:
    QIODevice * mDevice;
    Region mCurrentRegion;
    Region mQuery;





};
}}


#endif // ABSTRACTREGIONREADER_H
