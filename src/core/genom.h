#ifndef GENOM_H
#define GENOM_H
#include <QtCore>
#include "sequence.h"
namespace big {
class Genom
{
public:
    Genom(const QString& genomPath);

    int chromosomCount();
    int chromosomLength(const QString& chromosom);

    Sequence sequence(const QString& chromosom, qint64 pos, qint64 length);



};
}
#endif // GENOM_H
