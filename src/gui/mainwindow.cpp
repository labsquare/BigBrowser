#include "mainwindow.h"
#include "app.h"
#include "sequencetrack.h"
namespace big {
namespace gui {
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mMenuBar         = new QMenuBar();
    mMainToolBar     = new MainToolBar();
    mStatusBar       = new StatusBar();
    mchromosomWidget = new ChromosomWidget();
    mTrackListWidget = new TrackListWidget();
    mGenom           = new Genom();

    setMenuBar(mMenuBar);
    addToolBar(mMainToolBar);

    QSplitter * centralSplitter = new QSplitter(Qt::Vertical);
    centralSplitter->addWidget(mchromosomWidget);
    centralSplitter->addWidget(mTrackListWidget);

    mTrackListWidget->addTrack(new SequenceTrack());

    QVBoxLayout * centralLayout = new QVBoxLayout;
    centralLayout->addWidget(centralSplitter);
    centralLayout->addWidget(mStatusBar);
    centralLayout->setContentsMargins(0,0,0,0);

    QWidget * cWidget = new QWidget;
    cWidget->setLayout(centralLayout);


    setCentralWidget(cWidget);

//    mchromosomWidget->updateChromosom();

    mchromosomWidget->setMaximumHeight(130);
    resize(1000,600);

    setupMenuBar();

    setGenom("hg19");

}

void MainWindow::showSettings()
{
    SettingsDialog dialog(this);
    dialog.exec();


}

void MainWindow::setGenom(const QString &name)
{
    mGenom->load(App::i()->genomPath(name));

    mMainToolBar->setGenom(mGenom);
    mchromosomWidget->setGenom(mGenom);
}

void MainWindow::setupMenuBar()
{

    QMenu * fileMenu = menuBar()->addMenu("File");
    QAction * preferenceAction = fileMenu->addAction("Preference",this,SLOT(showSettings()));
    QAction * closeAction      = fileMenu->addAction("Close", this,SLOT(close()));





}
}}

