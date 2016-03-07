#include <QApplication>
#include <QDebug>
#include "app.h"
#include "mainwindow.h"
#include "sequence.h"
#include "genom.h"
#include "quazip.h"
#include "GUnzipDevice.h"
using namespace big::core;
using namespace big::gui;
using namespace qtGunzip;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App::i()->setDefaultDatabasePath();

    //    MainWindow win ;
    //    win.show();


    QFile qfile("/home/bioinfo/test.txt.gz");
    qfile.open(QIODevice::ReadOnly);


    QByteArray ar;
    // ar will be filled with extracted bytes
    int extractedBytes = GUnzipDevice::getBytes(&qfile, ar);

    qDebug()<<ar;


    return a.exec();
}
