#ifndef GFFREADER_H
#define GFFREADER_H
#include "abstracttextregionreader.h"

namespace big {
namespace core {

class GffReader : public AbstractTextRegionReader
{
public:
    GffReader(const QString& filename);

    Region parseLine(const QString &line) const;

};
}}

#endif // GFFREADER_H
