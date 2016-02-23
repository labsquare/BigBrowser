#include <QApplication>
#include <QDebug>
#include "abstractregionreader.h"
#include "bedreader.h"
#include "region.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    big::BedReader reader("file.bed");

    reader.setQuery("chr3", 10, 1000);

    while (reader.next())
    {
        qDebug()<<reader.region().chromosom();
    }




    return a.exec();
}
