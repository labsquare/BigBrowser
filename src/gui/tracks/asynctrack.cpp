#include "asynctrack.h"

namespace big {
namespace gui {



AsyncTrack::AsyncTrack(QGraphicsItem * parent )
    :AbstractTrack(parent)
{


    // Cache has factor=3 ... 1 visible and 2 hidden
    mCache.append(QPixmap(200,200));
    mCache.append(QPixmap(200,200));
    mCache.append(QPixmap(200,200));

    connect(&mWatcher,SIGNAL(finished()),
               this,SLOT(cacheCreated()));

}

AsyncTrack::~AsyncTrack()
{

}


void AsyncTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{
    Q_UNUSED(chromosom);
    Q_UNUSED(start);
    Q_UNUSED(end);


    if (!mCache.isEmpty()){
        int x= 0;
        foreach (QPixmap p, mCache)
        {
            x+=mCache.first().width();
            painter->drawPixmap(x,0, p);

        }


    }



}

void AsyncTrack::updateSelection()
{

    // Crash sinon...
    if (!mWatcher.isRunning())
    {
        // Lambda function C++11 !!
        future = QtConcurrent::map(mCache, [this](QPixmap& pix){this->createPixmap(pix);});
        mWatcher.setFuture(future);

    }

}

void AsyncTrack::createPixmap(QPixmap &pix)
{

    QColor col (qrand()%255,qrand()%255, qrand()%255);

    pix.fill(col);

    qDebug()<<pix<<"create";
}

void AsyncTrack::cacheCreated()
{

    qDebug()<<"created";

    update();
}





}}
