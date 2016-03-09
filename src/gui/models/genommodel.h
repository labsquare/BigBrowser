#ifndef GENOMMODEL_H
#define GENOMMODEL_H
#include <QAbstractTableModel>
#include <QtCore>
#include "quazip.h"
#include "quazipfile.h"
namespace big {
namespace gui {

struct GenomItem {
    QString id;
    QString name;
    QString filePath;
    QString absoluteFilePath;

    int size;
};


class GenomModel : public QAbstractTableModel
{
Q_OBJECT
public:
    GenomModel(QObject * parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


public Q_SLOTS:
    void loadList();
    bool removeFile(int row);
    bool addFile(const QString& path);


private:
    QList<GenomItem> mItems;
    QStringList mHeaders;


};

}} // end namespace

#endif // GENOMMODEL_H
