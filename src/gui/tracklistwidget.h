#ifndef TRACKLISTWIDGET_H
#define TRACKLISTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "abstracttrack.h"
namespace big {
namespace gui {
class TrackListWidget : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QString chromosom READ chromosom )
    Q_PROPERTY(quint64 start READ start() )
    Q_PROPERTY(quint64 end READ end )

public:
    explicit TrackListWidget(QWidget *parent = 0);
    void addTrack(AbstractTrack * track);

    const QString& chromosom() const;
    quint64 start() const;
    quint64 end() const;



public Q_SLOTS:
    void setSelection(const QString& chromosom, quint64 start, quint64 end);

Q_SIGNALS:
    void selectionChanged(const QString& chromosom, quint64 start, quint64 end);

private:
QList<AbstractTrack*> mTracks;
QGraphicsScene * mScene;
QString mChromosom;
quint64 mStart;
quint64 mEnd;


};

}}
#endif // TRACKLISTWIDGET_H
