#include "sequencetrack.h"

namespace big {
namespace gui {

SequenceTrack::SequenceTrack(const QString& filename,QGraphicsItem * parent)
    :AbstractTrack(parent)
{

    mDataModel = new FastaDataModel(filename);

    connect(mDataModel,SIGNAL(sequenceReceived(Sequence)),this,SLOT(setSequence(Sequence)));

}

void SequenceTrack::setSequence(const Sequence &seq)
{
    mSequence = seq;
    update();

}

void SequenceTrack::setSelection()
{
    qDebug()<<"set selection";

    if ( trackList()->end() - trackList()->start() < 100)
    mDataModel->setQuery(trackList()->chromosom(), trackList()->start(), trackList()->end());

}

void SequenceTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{

    qDebug()<<" truc ";
    painter->setBrush(QBrush(Qt::red));

    if (!mSequence.isEmpty() || mSequence.count() < 100)
    {

            qDebug()<<mSequence.toString();




    }





}

}} // end namespace
