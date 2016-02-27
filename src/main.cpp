#include <QApplication>
#include <QDebug>
#include "app.h"
#include "mainwindow.h"
#include "cytobandreader.h"
using namespace big;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App::i()->setDefaultDatabasePath();
    App::i()->setCurrentGenom("hg19");


    MainWindow w;
    w.show();

    return a.exec();
}
