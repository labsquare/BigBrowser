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

    setMenuBar(mMenuBar);
    addToolBar(mToolBar);
    addToolBar(mSearchBar);


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

    //    setSelection("chr1",1,100000);


    // ----------------------------------
    // Connect signals and slots
    // ----------------------------------

    // The selection signal/slot system is composed of 2 signals
    //  - selectionChanged is raised by UI control who allow user to select a custom region
    //  - selectionValidated is raised by the Tracklist who is the only one able to know if the selected region is drawable by tracks

    // Workflow :
    // 1) a UI control notify the mainwindow that the selection changed
    // 2) the main windows notify tracklist
    // 3) the tracklist validate the selection
    // 4) the mainwindows notify all other control with the validated selection

    // selectionChanged signal are raised by all UI control except the Tracklist
    connect(mSearchBar,SIGNAL(selectionChanged(QString,quint64,quint64)),
            this,SLOT(setSelection(QString,quint64,quint64)));
    connect(mchromosomWidget,SIGNAL(selectionChanged(QString,quint64,quint64)),
            this,SLOT(setSelection(QString,quint64,quint64)));

    // selectionValidated signal raised only by the tracklist
    connect(mTrackListWidget,SIGNAL(selectionValidated(QString,quint64,quint64)),
            this,SLOT(selectionValidated(QString,quint64,quint64)));




    connect(mStatusBar,SIGNAL(zoomChanged(int)),mchromosomWidget,SLOT(setZoom(int)));

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
    // Only the Tracklist is able to validate the selection
    // (the tracklist know how to compute the zoom level according the size of the scene)
    if (sender() != mTrackListWidget)
        mTrackListWidget->setSelection(chromosom,start,end);
}

void MainWindow::selectionValidated(const QString& chromosom, quint64 start, quint64 end)
{
    if (sender() != mchromosomWidget)
        mchromosomWidget->setSelection(chromosom,start,end);

    if (sender() != mSearchBar)
        mSearchBar->setSelection(chromosom,start,end);

    if (sender() != mStatusBar)
        mStatusBar->setSelection(chromosom,start,end);
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

