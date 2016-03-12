#ifndef ABSTRACTTEXTREGIONREADER_H
#define ABSTRACTTEXTREGIONREADER_H
#include <QtCore>
#include "abstractregionreader.h"
namespace big {
namespace core {

class AbstractTextRegionReader : public AbstractRegionReader
{
public:
    AbstractTextRegionReader(QIODevice * device);
    AbstractTextRegionReader(const QString& filename);

    virtual bool next();


protected:
    virtual Region parseLine(const QString& line) const = 0;



private:
    QTextStream mStream;


};

}} // end namespace

#endif // ABSTRACTTEXTREGIONREADER_H
