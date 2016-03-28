#include "selection.h"
namespace big {
namespace core {
Selection::Selection()
    :Region()
{

}
Selection::Selection(const QString &chromosom, quint64 start, quint64 end)
    :Region(chromosom,start,end)
{

}




}} // end namespace
