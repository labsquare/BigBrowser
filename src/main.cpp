#include <QApplication>
#include <QDebug>
#include <QSettings>
#include "quagzipfile.h"
#include "app.h"
#include "mainwindow.h"
#include "sequence.h"
#include "genom.h"
#include "quazip.h"
#include "vcfreader.h"
#include "genetoolwidget.h"

using namespace big::core;
using namespace big::gui;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("BIG");
    QCoreApplication::setOrganizationDomain("labsquare.org");
    QCoreApplication::setApplicationName("Big Browser");

    GeneToolWidget * widget = new GeneToolWidget;
    widget->show();




    //    QuaGzipFile * file = new QuaGzipFile("/home/schutz/cytoBand.txt.gz");

    //    CytobandReader reader(file);
    //    if (reader.open())
    //    {
    //        while (reader.next())
    //        {
    //            qDebug()<<reader.region().chromosom();
    //        }
    //    }

//    App::i()->loadSettings();

//    MainWindow win;
//    win.show();



    return a.exec();
}
