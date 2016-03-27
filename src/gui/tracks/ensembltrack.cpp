#include "ensembltrack.h"
#include <QDebug>
namespace big {
namespace gui {
EnsemblTrack::EnsemblTrack(QGraphicsItem * parent)
    :AbstractTrack(parent)
{

    mManager = new QNetworkAccessManager(this);
}

void EnsemblTrack::updateSelection()
{
    QString url = QString("http://rest.ensembl.org/sequence/region/human/%1:%2..%3:1")
            .arg(chromosom())
            .arg(start())
            .arg(end());


    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QNetworkReply * reply = mManager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(dataReceived()));


}

void EnsemblTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{

    painter->drawPixmap(0,0,mPixmap);


}

void EnsemblTrack::dataReceived()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());


    mSequence = core::Sequence(document.object().value("seq").toString().toUtf8());

    mPixmap = QPixmap(boundingRect().width(), height());
    mPixmap.fill(Qt::white);

    QPainter painter(&mPixmap);

    QMap<char, QColor> colors = {{'A',Qt::green},
                                 {'T', Qt::red},
                                 {'C', Qt::blue},
                                 {'G',Qt::black}
                                };

    // size of current font
    QFontMetrics metrics(painter.font());

    int x = 0;
    foreach ( char letter , mSequence.byteArray())
    {
    painter.setPen(colors.value(letter, Qt::gray));
    painter.drawText(x,height()/2, QString(letter));

    x+=metrics.width(QString(letter));

    }


    update(boundingRect());

}

}}
