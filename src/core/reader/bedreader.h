#ifndef BEDREADER_H
#define BEDREADER_H
#include "abstractregionreader.h"

namespace big{
namespace core {

class BedReader : public AbstractRegionReader
{
public:
    BedReader(const QString& filename);

    bool next() Q_DECL_OVERRIDE;
};

}}

#endif // BEDREADER_H
