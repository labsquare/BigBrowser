#ifndef RULERTRACK_H
#define RULERTRACK_H
#include "abstracttrack.h"


namespace big {
namespace gui {


class RulerTrack : public AbstractTrack
{
    Q_OBJECT
public:
    //! Default constructor
    //! @param parent
    RulerTrack(QGraphicsItem * parent = 0);

    //! Override the painter content method
    virtual void paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end);

};

}
}
#endif // RULERTRACK_H
