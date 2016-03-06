#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSplitter>
#include "maintoolbar.h"
#include "statusbar.h"
#include "tracklistwidget.h"
#include "chromosomwidget.h"
#include "settingsdialog.h"
#include "genom.h"

namespace big {
namespace gui {
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);



public Q_SLOTS:
void showSettings();
void setGenom(const QString& name);

protected:
    void setupMenuBar();


private:
    QMenuBar * mMenuBar;
    MainToolBar * mMainToolBar;
    StatusBar * mStatusBar;
    ChromosomWidget * mchromosomWidget;
    TrackListWidget * mTrackListWidget;
    Genom * mGenom;


};

}}

#endif // MAINWINDOW_H
