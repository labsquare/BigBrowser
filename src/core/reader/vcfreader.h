#ifndef VCFREADER_H
#define VCFREADER_H
#include "abstractregionreader.h"
namespace big {
namespace core {

class VcfReader : public AbstractRegionReader
{
public:
    VcfReader(const QString& filename);

    bool next() Q_DECL_OVERRIDE;
};

}}
#endif // VCFREADER_H
