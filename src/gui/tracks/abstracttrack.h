#ifndef ABSTRACTTRACK_H
#define ABSTRACTTRACK_H
#include <QGraphicsObject>
#include <QContiguousCache>
namespace big {
namespace gui {

class AbstractTrack : public QGraphicsObject
{
    Q_OBJECT
public:
    AbstractTrack(QGraphicsItem * parent = 0);

protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void setSelection(const QString& chromosom, quint64 start, quint64 end);

    const QString& chromosom() const ;
    quint64 start() const;
    quint64 end() const;


Q_SIGNALS:
    void selectionChanged(const QString& chromosom, quint64 start, quint64 end);


private:
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;

};

}} // end namespace

#endif // ABSTRACTTRACK_H
