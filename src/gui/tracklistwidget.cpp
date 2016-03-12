#include "tracklistwidget.h"
namespace big {
namespace gui {
TrackListWidget::TrackListWidget(QWidget *parent) : QGraphicsView(parent)
{
    mScene = new QGraphicsScene;
    setScene(mScene);


    //    setResizeAnchor(QGraphicsView::NoAnchor);
    //    setTransformationAnchor(QGraphicsView::NoAnchor	);

    //    mScene->setSceneRect(rect());



}

void TrackListWidget::addTrack(AbstractTrack *track)
{
    track->setTrackList(this);
    track->setRow(mTracks.count());
    mTracks.append(track);
    scene()->addItem(track);
    track->setPos(0,track->boundingRect().height() * (mTracks.count()-1));

    connect(track,SIGNAL(rowChanged(int,int)),this,SLOT(rearrage(int,int)));

}

const QString &TrackListWidget::chromosom() const
{
    return mChromosom;
}

quint64 TrackListWidget::start() const
{
    return mStart;
}

quint64 TrackListWidget::end() const
{
    return mEnd;
}

int TrackListWidget::rowToPixel(int row) const
{
    // Convert index of track to the top  coordinaite
    int y = 0;
    for (int i=0; i<row; ++i)
    {
        y += mTracks.at(i)->height();
    }
    return y;
}

int TrackListWidget::rowFromPixel(int y) const
{

    // Convert top y coordinaite to the row index
    int size = 0;
    int row  =0;
    for ( int index = 0; index < mTracks.count(); ++index)
    {
        size += mTracks.at(row)->height();
        if ( size > y){
            row = index;
            break;
        }
    }



    return row;
}

QList<AbstractTrack *> TrackListWidget::tracks()
{
    return mTracks;
}


void TrackListWidget::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    mChromosom = chromosom;
    mStart = start;
    mEnd = end;
}

void TrackListWidget::resizeEvent(QResizeEvent *event)
{
    // If I do not put 2000 .. I Do not have the scrollbar !

    mScene->setSceneRect(QRectF(0,0,event->size().width(),2000));


    QGraphicsView::resizeEvent(event);

}

void TrackListWidget::rearrage(int from, int to)
{
    /*
     * THIS IS WHERE @OLIVIER HAS TO WORK...
     Selected items call this methods, when their row change "from" to "to"

    */

    // ensure this is only called by a trackItem
    if (!sender())
        return ;


    // the sender of the signals
    AbstractTrack * track = qobject_cast<AbstractTrack*>(sender());

    qDebug()<<"from "<<from<<" to "<<to;

    if ( to > from )
    {

        foreach ( AbstractTrack * t , mTracks)
        {
            if (t != track)
            {
                if (( t->row() <= to) && t->row() > from)
                {
                    qDebug()<<"move item"<<t->row();
                    t->setRow(t->row()>0 ? t->row()-1: 0);
                    t->updatePositionFromRow();
                }
            }

        }

    }



    track->setRow(to);


}

}}
