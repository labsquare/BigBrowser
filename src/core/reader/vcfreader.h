#ifndef VCFREADER_H
#define VCFREADER_H
#include "abstracttextregionreader.h"
namespace big {
namespace core {

class VcfReader : public AbstractTextRegionReader
{
public:
    VcfReader(const QString& filename);

    Region parseLine(const QString &line) const;

};

}}
#endif // VCFREADER_H
