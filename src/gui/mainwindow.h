#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "maintoolbar.h"

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


};

#endif // MAINWINDOW_H
