#ifndef SEQUENCETRACK_H
#define SEQUENCETRACK_H
#include "abstracttrack.h"
#include "sequence.h"
namespace big {
namespace gui {
using namespace core;

class SequenceTrack : public AbstractTrack
{
    Q_OBJECT
public:
    // Config parameter (could be set by enduser via track configs panel)
    const bool C_MAGNIFIER_ENABLE = true;
    const int C_MAGNIFIER_BASE_WIDTH = 5;


    SequenceTrack(QGraphicsItem * parent = 0);



    //! Override the painter content method
    virtual void paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end);
    //! Override the painter cursor method
    virtual void paintCursorLayer(QPainter * painter);


private:
    Sequence mFakeSequence;
    QColor baseToColor(char base);
    void baseWidthToFont(float baseWidth, QFont * font);

    QMap<char, QColor> mBaseColors;
};
}}

#endif // SEQUENCETRACK_H
