#ifndef SELECTION_H
#define SELECTION_H
#include <QtCore>
#include "region.h"
namespace big {
namespace core {
class Selection
{
public:
    Selection();
    Selection(const QString& chromosom, quint64 start, quint64 end);

    QString chromosom() const;
    void setChromosom(const QString &chromosom);

    quint64 start() const;
    void setStart(const quint64 &start);

    quint64 end() const;
    void setEnd(const quint64 &end);

     Region toRegion();
     void fromRegion(const Region& region);

private:
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;
};

}} // end namespace

#endif // SELECTION_H
