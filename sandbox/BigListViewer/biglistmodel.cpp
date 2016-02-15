#include "biglistmodel.h"
#include <QTextStream>
#include <QDebug>
BigListModel::BigListModel(const QString &filename, QObject *parent):
    QAbstractListModel(parent)
{

    mFile.setFileName(filename);





}

int BigListModel::rowCount(const QModelIndex &parent) const
{

    if (!mFile.isOpen())
        return 0;

    return mCount;

}


QVariant BigListModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole)
    {
        return mCache.at(index.row());
    }


    return QVariant();
}

bool BigListModel::canFetchMore(const QModelIndex &parent) const
{
    if ( mCount < mLines)
        return true;

    else return false;
}

void BigListModel::fetchMore(const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), mCount, mCount + 100 -1);
    cacheRow(mCount, mCount+100);
    mCount += 100;
    endInsertRows();

}




bool BigListModel::load()
{

    if(mFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {

        mStream.setDevice(&mFile);
        mCount = 100;
        mLines = mFile.size() / 9;
        mCache.setCapacity(200);

        cacheRow(0,100);
    }

    return true;

}

void BigListModel::cacheRow(int from, int to) const
{

    mStream.seek(from * 9);
    int index = 0;
    while (!mStream.atEnd() && index < to - from)
    {
        mCache.append(mStream.readLine());

        ++index;

    }


}
