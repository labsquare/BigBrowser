#ifndef SEQUENCETRACK_H
#define SEQUENCETRACK_H
#include "abstracttrack.h"

namespace big {
namespace gui {

class SequenceTrack : public AbstractTrack
{
    Q_OBJECT
public:
    SequenceTrack(QGraphicsItem * parent = 0);
};
}}

#endif // SEQUENCETRACK_H
