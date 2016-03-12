#ifndef BEDGRAPHREADER_H
#define BEDGRAPHREADER_H
#include "abstracttextregionreader.h"
namespace big {
namespace core {
class BedGraphReader : public AbstractTextRegionReader
{
public:
    BedGraphReader(const QString& filename);

    bool next() Q_DECL_OVERRIDE;
};

}}

#endif // BEDGRAPHREADER_H
