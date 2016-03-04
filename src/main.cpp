#include <QApplication>
#include <QDebug>
#include "app.h"
#include "mainwindow.h"
#include "cytobandreader.h"
#include "sequence.h"
#include "genom.h"
using namespace big::core;
using namespace big::gui;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App::i()->setDefaultDatabasePath();
    App::i()->setCurrentGenom("hg19");


//   Genom genom(App::i()->currentGenomFilePath("hg19.fa"));

    Genom genom(App::i()->currentGenomFilePath("hg19.fa"));

    qDebug()<<genom.hasIndex();

    qDebug()<<genom.sequence("chr1",1000000,20).toString();




    MainWindow win ;
    win.show();


    return a.exec();
}
