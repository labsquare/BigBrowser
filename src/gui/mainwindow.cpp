#include "mainwindow.h"
#include "app.h"
#include "sequencetrack.h"
#include "rulertrack.h"
#include "asynctrack.h"
namespace big {
namespace gui {
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mMenuBar         = new QMenuBar();
    mSearchBar       = new SearchToolBar();
    mToolBar         = new QToolBar();
    mStatusBar       = new StatusBar();
    mchromosomWidget = new ChromosomWidget();
    mTrackListWidget = new TrackListWidget();
    mGenom           = new Genom();
    mRouter          = new SelectionRouter();

    setMenuBar(mMenuBar);
    addToolBar(mToolBar);
    addToolBar(mSearchBar);

    mRouter->addComponent(mchromosomWidget);
    mRouter->addComponent(mTrackListWidget);
    mRouter->addComponent(mSearchBar);



    QSplitter * centralSplitter = new QSplitter(Qt::Vertical);
    centralSplitter->addWidget(mchromosomWidget);
    centralSplitter->addWidget(mTrackListWidget);

    mTrackListWidget->addTrack(new RulerTrack());
    mTrackListWidget->addTrack(new AsyncTrack());
    mTrackListWidget->addTrack(new SequenceTrack());
    mTrackListWidget->addTrack(new SequenceTrack());
    //mTrackListWidget->addTrack(new SequenceTrack());
    //mTrackListWidget->addTrack(new SequenceTrack());


    QVBoxLayout * centralLayout = new QVBoxLayout;
    centralLayout->addWidget(centralSplitter);
    centralLayout->addWidget(mStatusBar);
    centralLayout->setContentsMargins(0,0,0,0);

    QWidget * cWidget = new QWidget;
    cWidget->setLayout(centralLayout);


    setCentralWidget(cWidget);


    mchromosomWidget->setFixedHeight(130);
    resize(1000,600);

    setupMenuBar();


    connect(mSearchBar,SIGNAL(genomChanged(QString)),this,SLOT(setGenom(QString)));


    // Load a genom if not exists
    if (!App::i()->avaibleGenoms().isEmpty())
        setGenom(App::i()->avaibleGenoms().first());



}

MainWindow::~MainWindow()
{
    delete mMenuBar;
    delete mSearchBar;
    delete mToolBar;
    delete mStatusBar;
    delete mchromosomWidget;
    delete mTrackListWidget;
    delete mGenom;
    delete mRouter;
}

void MainWindow::showSettings()
{
    SettingsDialog dialog(this);
    if (dialog.exec()){
        mSearchBar->loadAvaibleGenom();
        // Load a genom if not exists
        if (!App::i()->avaibleGenoms().isEmpty())
            setGenom(App::i()->avaibleGenoms().first());

    }


}

void MainWindow::setGenom(const QString &name)
{
    mGenom->load(App::i()->genomPath(name));

    mSearchBar->setGenom(mGenom);
    mchromosomWidget->setGenom(mGenom);
    mTrackListWidget->setGenom(mGenom);
    //    mStatusBar->setGenom(mGenom);
}

void MainWindow::setSelection(const QString &chromosom, quint64 start, quint64 end)
{
    mRouter->setSelection(Region(chromosom,start,end));
}
void MainWindow::setupMenuBar()
{

    QMenu * fileMenu = menuBar()->addMenu("File");
    QAction * preferenceAction = fileMenu->addAction(App::awesome()->icon(fa::wrench),"Preference",this,SLOT(showSettings()));
    QAction * closeAction      = fileMenu->addAction(App::awesome()->icon(fa::times),"Close", this,SLOT(close()));


    QAction * chromAction = mToolBar->addAction(App::awesome()->icon(fa::eye),"show chromosom",mchromosomWidget,SLOT(setVisible(bool)));
    chromAction->setCheckable(true);
    chromAction->setChecked(true);

    mToolBar->addAction(preferenceAction);
    mToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

}
}}

