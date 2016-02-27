#ifndef REGIONLIST_H
#define REGIONLIST_H
#include <QList>
#include "region.h"
namespace big {
class RegionList : public QList<Region>
{
public:
    RegionList() Q_DECL_NOTHROW {}
};

}
#endif // REGIONLIST_H
