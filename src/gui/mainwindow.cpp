#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mMenuBar = new QMenuBar();
    mMainToolBar = new MainToolBar();

    setMenuBar(mMenuBar);
    addToolBar(mMainToolBar);


    resize(1000,600);

    setupMenuBar();
}

void MainWindow::setupMenuBar()
{

    menuBar()->addMenu("File");


}


