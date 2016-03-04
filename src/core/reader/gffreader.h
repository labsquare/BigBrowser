#ifndef GFFREADER_H
#define GFFREADER_H
#include "abstractregionreader.h"
namespace big {
namespace core {

class GffReader : public AbstractRegionReader
{
public:
    GffReader(const QString& filename);

    bool next() Q_DECL_OVERRIDE;
};
}}

#endif // GFFREADER_H
