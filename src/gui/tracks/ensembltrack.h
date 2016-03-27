#ifndef ENSEMBLTRACK_H
#define ENSEMBLTRACK_H
#include "abstracttrack.h"
#include <QtNetwork>
#include <QJsonDocument>
#include <QPainter>
#include "sequence.h"

namespace big {
namespace gui {

class EnsemblTrack : public AbstractTrack
{
    Q_OBJECT
public:
    EnsemblTrack(QGraphicsItem * parent = 0);
    virtual void updateSelection();

    virtual void paintRegion(QPainter *painter, const QString& chromosom, quint64 start, quint64 end);

protected Q_SLOTS:
    void dataReceived();


private:
    QPixmap mPixmap;
    QNetworkAccessManager * mManager;
    core::Sequence mSequence;


};

}}

#endif // ENSEMBLTRACK_H
