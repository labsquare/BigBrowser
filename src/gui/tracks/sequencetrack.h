#ifndef SEQUENCETRACK_H
#define SEQUENCETRACK_H
#include "abstracttrack.h"
#include "fastadatamodel.h"
#include "tracklistwidget.h"
#include <QPainter>
namespace big {
namespace gui {

using namespace core;

class SequenceTrack : public AbstractTrack
{
    Q_OBJECT
public:
    SequenceTrack(const QString& filename, QGraphicsItem * parent = 0);


public Q_SLOTS:
    void setSequence(const Sequence& seq);
    void setSelection();

protected:
    virtual void paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end);

private:
    FastaDataModel * mDataModel;
    Sequence mSequence;


};
}}

#endif // SEQUENCETRACK_H
