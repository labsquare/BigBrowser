#ifndef ASYNCTRACK_H
#define ASYNCTRACK_H
#include "abstracttrack.h"
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QPainter>
namespace big {
namespace gui {

class AsyncTrack : public AbstractTrack
{
    Q_OBJECT
public:
    AsyncTrack(QGraphicsItem * parent = 0);
    ~AsyncTrack();

    virtual void paintRegion(QPainter *painter, const QString& chromosom, quint64 start, quint64 end);

    virtual void updateSelection();
    virtual QPixmap createPixmap(const QString& chromosom, quint64 start, quint64 end);

    bool isRunning() const;

protected Q_SLOTS:
    void pixmapFinished();

private:
    QFutureWatcher<QPixmap> * mWatcher;
    QFuture<QPixmap> mFuture;
    bool mCancelThread;
};


}}
#endif // ASYNCTRACK_H
