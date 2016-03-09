#include "genommodel.h"
#include "app.h"
#include <QDebug>
namespace big {
namespace gui {

GenomModel::GenomModel(QObject * parent)
    :QAbstractTableModel(parent)
{

    mHeaders<<"id"<<"name"<<"size";
    //    loadList();

}

int GenomModel::rowCount(const QModelIndex &parent) const
{
    return mItems.count();
}

int GenomModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}



QVariant GenomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return mItems.at(index.row()).filePath;

        if (index.column() == 1)
            return mItems.at(index.row()).name;

        if (index.column() == 2)
            return mItems.at(index.row()).size;

    }

    return QVariant();
}

QVariant GenomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( orientation == Qt::Horizontal)
    {
        if ( role == Qt::DisplayRole)
        {
            return mHeaders.value(section,"no name");
        }
    }
    return QVariant();
}

void GenomModel::loadList()
{
    beginResetModel();
    mItems.clear();
    QDir genomFolder(App::i()->genomPath());
    genomFolder.setNameFilters(QStringList()<<"*.genome");
    foreach (QFileInfo fileInfo, genomFolder.entryInfoList(QDir::Files|QDir::NoDotAndDotDot))
    {
        QuaZip zip(fileInfo.absoluteFilePath());
        if (zip.open(QuaZip::mdUnzip))
        {
            QuaZipFile file(&zip);
            if (zip.setCurrentFile("property.txt"))
            {
                if(file.open(QIODevice::ReadOnly))
                {
                    QTextStream stream(&file);
                    QHash<QString,QVariant> mProperties;
                    while (!stream.atEnd())
                    {
                        QStringList line = stream.readLine().split("=");
                        if (line.count() == 2)
                            mProperties.insert(line[0], line[1]);
                    }

                    // Create item
                    GenomItem item;
                    item.filePath = fileInfo.fileName();
                    item.id       = mProperties.value("id","unknown").toString();
                    item.name     = mProperties.value("name","uknown").toString();
                    item.size     = fileInfo.size();
                    item.absoluteFilePath = fileInfo.absoluteFilePath();
                    mItems.append(item);
                }
            }

        }
    }

    endResetModel();

}

bool GenomModel::removeFile(int row)
{
    if (row >= mItems.count() )
        return false;

    GenomItem item = mItems.at(row);

    if (QFile::remove(item.absoluteFilePath))
    {
        loadList();
        return true;
    }

    return false;

}

bool GenomModel::addFile(const QString &path)
{
    QFileInfo info(path);
    if (QFile::copy(info.absoluteFilePath(), App::i()->genomPath(info.fileName()))){
        loadList();
        return true;
    }
    return false;
}



}}
