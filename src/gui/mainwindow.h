#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSplitter>
#include "maintoolbar.h"
#include "statusbar.h"
#include "tracklistwidget.h"
#include "chromosomwidget.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void setupMenuBar();


private:
    QMenuBar * mMenuBar;
    MainToolBar * mMainToolBar;
    StatusBar * mStatusBar;
    ChromosomWidget * mchromosomWidget;
    TrackListWidget * mTrackListWidget;



};

#endif // MAINWINDOW_H
