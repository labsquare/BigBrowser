#include "mainwindow.h"
#include "app.h"
namespace big {
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mMenuBar         = new QMenuBar();
    mMainToolBar     = new MainToolBar();
    mStatusBar       = new StatusBar();
    mchromosomWidget = new ChromosomWidget();
    mTrackListWidget = new TrackListWidget();

    setMenuBar(mMenuBar);
    setStatusBar(mStatusBar);
    addToolBar(mMainToolBar);

    QSplitter * centralSplitter = new QSplitter(Qt::Vertical);
    centralSplitter->addWidget(mchromosomWidget);
    centralSplitter->addWidget(mTrackListWidget);


    setCentralWidget(centralSplitter);

    mchromosomWidget->loadCytoBand(App::i()->currentGenomFilePath("hg19.cytoBand"));



    resize(1000,600);

    setupMenuBar();
}

void MainWindow::setupMenuBar()
{

    menuBar()->addMenu("File");


}
}

