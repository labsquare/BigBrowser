#ifndef SELECTION_H
#define SELECTION_H
#include <QtCore>
#include "region.h"
namespace big {
namespace core {
class Selection :public Region
{
public:
    Selection();
    Selection(const QString& chromosom, quint64 start, quint64 end);



};

}} // end namespace

#endif // SELECTION_H
