#include <QApplication>
#include <QDebug>
#include "abstractregionreader.h"
#include "bedreader.h"
#include "region.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    big::BedReader reader("/home/bioinfo/Dev/BigBrowser/knownGene.hg18.chr21.bed");

    if (reader.open(QIODevice::ReadOnly))
    {
        reader.region(0);
    }





    return a.exec();
}
