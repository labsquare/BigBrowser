#ifndef BEDREADER_H
#define BEDREADER_H
#include "abstracttextregionreader.h"

namespace big{
namespace core {

class BedReader : public AbstractTextRegionReader
{
public:
    BedReader(const QString& filename);

    Region parseLine(const QString &line) const;

};

}}

#endif // BEDREADER_H
