#include <QApplication>
#include <QDebug>
#include "app.h"
#include "mainwindow.h"
#include "sequence.h"
#include "genom.h"
using namespace big::core;
using namespace big::gui;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App::i()->setDefaultDatabasePath();

    Sequence seq;

//    MainWindow win ;
//    win.show();


    return a.exec();
}
