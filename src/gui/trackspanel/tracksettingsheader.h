#ifndef TRACKSETTINGSHEADER_H
#define TRACKSETTINGSHEADER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVariantAnimation>
#include <QMouseEvent>
namespace big {
namespace gui {
class TrackSettingsHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TrackSettingsHeader(QWidget *parent = 0);

public Q_SLOTS:
    void setExpand(bool setExpand = true);
    bool isExpand() const;

signals:
    void expandChanged(bool expand);

protected:
void paintEvent(QPaintEvent * event);
void mousePressEvent(QMouseEvent * event);


private:
QString mTitle;
QVariantAnimation mAngle;
bool mIsExpand;

};

}} // end namespace
#endif // TRACKSETTINGSHEADER_H
