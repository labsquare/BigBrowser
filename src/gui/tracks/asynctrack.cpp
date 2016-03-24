#include "asynctrack.h"

namespace big {
namespace gui {
AsyncTrack::AsyncTrack(QGraphicsItem * parent )
    :AbstractTrack(parent)
{
    mWatcher = new QFutureWatcher<QPixmap>(this);


}

void AsyncTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{
    Q_UNUSED(chromosom);
    Q_UNUSED(start);
    Q_UNUSED(end);

    qDebug()<<mFuture.isRunning();

    if (mFuture.isRunning())
        painter->drawText(boundingRect(), Qt::AlignHCenter|Qt::AlignVCenter, "LOADING.....");
    else
        painter->drawPixmap(0,0,mFuture.result());


}

void AsyncTrack::updateSelection()
{

    if (mFuture.isRunning())
        mFuture.cancel();
    // Start thread
    mFuture = QtConcurrent::run(this, &AsyncTrack::createPixmap, chromosom(), start(), end());
    mWatcher->setFuture(mFuture);
    connect(mWatcher,SIGNAL(finished()),this,SLOT(pixmapFinished()));
    update();



}

QPixmap AsyncTrack::createPixmap(const QString &chromosom, quint64 start, quint64 end)
{
    qDebug()<<"start thread";
    // Compute in thread... long process
    double a = 0;
    for ( double i = 0; i < 1000000000; ++i)
    {
        a = i * i / i * i + sqrt(40000);

    }


    QPixmap pix = QPixmap(400,200);
    pix.fill(QColor(qrand()%200, qrand()%200, 250));


    return pix;


}

bool AsyncTrack::isRunning() const
{
    return mFuture.isRunning();
}

void AsyncTrack::pixmapFinished()
{
    qDebug()<<"end thread";

    // @olivier : this doesnt call updateContent ! It should !
    update(boundingRect());


}

}}
