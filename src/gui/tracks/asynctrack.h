#ifndef ASYNCTRACK_H
#define ASYNCTRACK_H
#include "abstracttrack.h"
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QPainter>
#include <QPaintEvent>
#include "region.h"

namespace big {
namespace gui {
using namespace core;
class AsyncTrack : public AbstractTrack
{
    Q_OBJECT
public:
    AsyncTrack(QGraphicsItem * parent = 0);
    ~AsyncTrack();

    virtual void paintRegion(QPainter *painter, const QString& chromosom, quint64 start, quint64 end);

    virtual void updateSelection();

    void createPixmap(QPixmap &pix);

protected Q_SLOTS:
    void cacheCreated();



private:
    QList<QPixmap> mCache;
    QFutureWatcher<void> mWatcher;
    QFuture<void> future;

};


}}
#endif // ASYNCTRACK_H
