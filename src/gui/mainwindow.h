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

namespace big {
namespace gui {
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);


public Q_SLOTS:
void showSettings();

protected:
    void setupMenuBar();


private:
    QMenuBar * mMenuBar;
    MainToolBar * mMainToolBar;
    StatusBar * mStatusBar;
    ChromosomWidget * mchromosomWidget;
    TrackListWidget * mTrackListWidget;

    core::Selector * mSelection;

};

}}

#endif // MAINWINDOW_H
