#ifndef ABSTRACTREGIONREADER_H
#define ABSTRACTREGIONREADER_H
#include <QObject>
#include <QIODevice>
#include "region.h"
#include "regionlist.h"
namespace big {



class AbstractRegionReader
{

public:
    AbstractRegionReader(QIODevice * device);
    AbstractRegionReader(const QString& filename);

    /*!
     * \brief currentLine
     * \return the current line number of reader
     */
    qint64 currentLine() const;

    /*!
     * \brief reset
     *
     * Reset current internal state to 0. Current Line will be set to 0
     */
    virtual void reset();


    /*!
    * \brief region
    * \return current Region according to the current line
    */
   const Region &region() const;

   /*!
    * \brief regions
    *
    * Load all regions into a RegionList.
    * !!WARNING!! Do not use this methods for large file. This load all region into memory
    * \return a list of all region
    */
   RegionList regions();

   /*!
    * \brief next
    *
    * iter to the next line and set the new region
    * \return True if success. If the end of file is reach , return false
    */
   virtual bool next() = 0;




protected:
    QIODevice * device();
    void setRegion(const Region& region);
    void setCurrentLine(qint64 line);




private:
    QIODevice * mDevice;
    Region mRegion;
    qint64 mCurrentLine;





};
}


#endif // ABSTRACTREGIONREADER_H
