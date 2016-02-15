#ifndef BIGLISTMODEL_H
#define BIGLISTMODEL_H
#include <QAbstractListModel>
#include <QFile>
#include <QTextStream>
#include <QContiguousCache>

class BigListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    BigListModel(const QString& filename, QObject * parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);

public slots:
    bool load();
    void cacheRow(int from, int to) const;


private:
    mutable QFile mFile;
    mutable QTextStream mStream;
    mutable QContiguousCache<QString> mCache;
    int mCount;
    int mLines;
};

#endif // BIGLISTMODEL_H
