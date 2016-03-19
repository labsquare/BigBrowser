#ifndef ABSTRACTDATAMODEL_H
#define ABSTRACTDATAMODEL_H

#include <QObject>
#include <QtCore>
#include "region.h"
#include "sequence.h"

namespace big {
namespace core {


class AbstractDataModel : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDataModel(QObject *parent = 0);
    bool isloading() const;

public Q_SLOTS:
    virtual void setQuery(const QString& chromosom, quint64 start , quint64 end) = 0;




protected:
    void setLoading(bool enable);



private:
    bool mLoading;



};

}} // end namespace

#endif // ABSTRACTDATAMODEL_H
