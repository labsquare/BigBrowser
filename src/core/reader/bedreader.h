#ifndef BEDREADER_H
#define BEDREADER_H
#include "abstractregionreader.h"
#include <QStringListModel>
#include <QTextStream>

namespace big{

class BedReader : public AbstractRegionReader
{
public:
    BedReader(const QString& filename);


     Region region(int row)  Q_DECL_OVERRIDE ;
     int count()   Q_DECL_OVERRIDE;

private:
     QTextStream mStream;

};

}
#endif // BEDREADER_H
