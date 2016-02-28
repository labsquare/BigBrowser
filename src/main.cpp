#include <QApplication>
#include <QDebug>
#include "app.h"
#include "mainwindow.h"
#include "cytobandreader.h"
#include "sequence.h"
using namespace big;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App::i()->setDefaultDatabasePath();
    App::i()->setCurrentGenom("hg19");


    Sequence seq("ACGTGGCT");


//    MainWindow w;
//    w.show();

    return a.exec();
}
