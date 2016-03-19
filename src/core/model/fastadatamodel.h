#ifndef FASTADATAMODEL_H
#define FASTADATAMODEL_H
#include <QtCore>
#include "abstractdatamodel.h"
#include "sequence.h"
namespace big {
namespace core {
class FastaDataModel : public AbstractDataModel
{
    Q_OBJECT
public:
    enum FileType{
        SequenceFile,
        IndexFile
    };

    FastaDataModel(const QString& filename = QString(), QObject * parent = 0);

    void setFilename(const QString& filename);
    const QString &filename(FileType type = SequenceFile) const;

    static bool createIndex(const QString& fastafile);
    bool isValid();



public Q_SLOTS:
    virtual void setQuery(const QString& chromosom, quint64 start , quint64 end);


Q_SIGNALS:
    void sequenceReceived(const Sequence& sequence);





private:
    QString mFilename;
    QString mIndexFilename;
};



}} // end namespace

#endif // FASTADATAMODEL_H
