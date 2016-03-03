#include "genom.h"
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
namespace big {
namespace core {
Genom::Genom(const QString &filename)
    :mFilename(filename)
{
    QFileInfo info(filename);
    mName = info.baseName();
}

int Genom::chromosomCount()
{

}

int Genom::chromosomLength(const QString &chromosom)
{

}

Sequence Genom::sequence(const QString &chromosom, qint64 pos, qint64 length)
{

}

const QString &Genom::name() const
{
    return mName;
}

const QString &Genom::filename() const
{
    return mFilename;
}

bool Genom::isValid()
{
    return QFile::exists(mFilename);
}

bool Genom::hasIndex()
{
    return QFile::exists(mFilename+".fai");

}

bool Genom::createIndex()
{

    QFile file(mFilename);
    QFile outputFile(mFilename+".fai");

    QTextStream stream(&outputFile);

    if (file.open(QIODevice::ReadOnly))
    {

        qint64 lineNumber = 0;
        qint64 baseCount  = 0;
        QByteArray name;
        int firstOffset = 0;
        int lineBaseSize= 0;
        int lineSize    = 0;

        while (!file.atEnd())
        {
            QByteArray line = file.readLine();

            if ( line.startsWith(">") && lineNumber != 0)
                stream<<name<<"\t"<<baseCount<<"\t"<<firstOffset<<"\t"<<lineBaseSize<<"\t"<<lineSize<<"\n";

            // Detect line number
            //-------------------------------------
            if (line.startsWith(">"))
            {
                name        = line.right(line.size()-1).simplified();
                firstOffset = file.pos();
            }
            //-------------------------------------
            else {
                baseCount += line.simplified().size();
                if (!lineSize){
                    lineBaseSize = line.simplified().size();
                    lineSize     =  line.size();
                }
            }

            ++lineNumber;
        }
        // last line ...
        stream<<name<<"\t"<<baseCount<<"\t"<<firstOffset<<"\t"<<lineBaseSize<<"\t"<<lineSize<<"\n";




    }
    file.close();

    // Write results to index file
    if (outputFile.open(QIODevice::WriteOnly))
    {
        stream.flush();
        outputFile.close();

    }
}

}}
