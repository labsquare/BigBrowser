#include <QApplication>
#include <QDebug>
#include "app.h"
#include "mainwindow.h"
#include "sequence.h"
#include "genom.h"
#include "quazip.h"

using namespace big::core;
using namespace big::gui;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App::i()->setDefaultPath();

    MainWindow win;
    win.show();



    return a.exec();
}
