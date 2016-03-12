#ifndef TRACKLISTWIDGET_H
#define TRACKLISTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QDebug>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QResizeEvent>
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

    int rowToPixel(int row) const;
    int rowFromPixel(int y) const;

    QList<AbstractTrack*> tracks();




public Q_SLOTS:
    void setSelection(const QString& chromosom, quint64 start, quint64 end);
    void rearrange(AbstractTrack * movingTrack, bool withAnimation=true);

Q_SIGNALS:
    void selectionChanged(const QString& chromosom, quint64 start, quint64 end);


protected:
    void resizeEvent(QResizeEvent * event);

private:
QList<AbstractTrack*> mTracks;
QGraphicsScene * mScene;
QString mChromosom;
quint64 mStart;
quint64 mEnd;


};

}}
#endif // TRACKLISTWIDGET_H
