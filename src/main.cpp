#include <QApplication>
#include <QDebug>
#include "app.h"
//#include "mainwindow.h"
#include "sequence.h"
#include "genom.h"
#include "quazip.h"

using namespace big::core;
//using namespace big::gui;

int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);
    //    App::i()->setDefaultDatabasePath();


    Genom genom(new QFile("/home/sacha/igv/genomes/hg19.genome"));

    qDebug()<<genom.isValid();



    //    QuaZip zip("c:/test.zip");
    //    zip.open(QuaZip::mdUnzip);
    //    qDebug()<<zip.getFileNameList();


    //    return a.exec();
}
