#ifndef TRACKSSETTINGSCONTAINER_H
#define TRACKSSETTINGSCONTAINER_H

#include <QWidget>
#include <QtWidgets>
#include "tracksettingsheader.h"
namespace big {
namespace gui {
class TracksSettingsContainer : public QWidget
{
    Q_OBJECT
public:
    explicit TracksSettingsContainer(QWidget *parent = 0);

    void setWidget(QWidget * widget);

public Q_SLOTS:
    void expand(bool expand = true);
    void collapse(bool collapse = true);

private:
    QWidget * mContent;
    QLabel * mTitleLabel;
    QLabel * mIconLabel;
    QToolButton * mToolButton;
    TrackSettingsHeader * mHeader;



};

}} // end namespace

#endif // TRACKSSETTINGSCONTAINER_H
