#ifndef BEDGRAPHREADER_H
#define BEDGRAPHREADER_H
#include "abstractregionreader.h"
namespace big {
namespace core {
class BedGraphReader : public AbstractRegionReader
{
public:
    BedGraphReader(const QString& filename);

    bool next() Q_DECL_OVERRIDE;
};

}}

#endif // BEDGRAPHREADER_H
