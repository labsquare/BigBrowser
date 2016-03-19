#include "fastadatamodel.h"
#include <QDebug>
namespace big {
namespace core {
FastaDataModel::FastaDataModel(const QString &filename, QObject *parent)
    :AbstractDataModel(parent)
{

    setFilename(filename);
}

void FastaDataModel::setFilename(const QString &filename)
{
    mFilename      = filename;
    mIndexFilename = mFilename+".fai";

}

const QString &FastaDataModel::filename(FastaDataModel::FileType type) const
{
    if (type == IndexFile)
        return mIndexFilename;

    return mFilename;

}

bool FastaDataModel::createIndex(const QString& fastafile)
{
    //The purpose of this function is to create an index file <filename.fa>.fai following the rule
    // from http://www.htslib.org/doc/faidx.html


    if (!QFile::exists(fastafile))
        return false;

    // This is the genome fileq
    QFile file(fastafile);

    // This is the index file to be generated
    QFile outputFile(fastafile+".fai");

    // Create a text stream to easily read inside the genome file
    QTextStream stream(&outputFile);

    if (file.open(QIODevice::ReadOnly))
    {
        // How many line of seq for chromosom X
        quint64 lineNumber = 0;

        // How many base of seq for chromosom x
        quint64 baseCount  = 0;

        // The name of chromosome x : eg  chr3
        QByteArray name;

        // The byte offset where the sequence start for chromosom X
        quint64 firstOffset = 0;

        // the line size without endl (depends on platform)
        quint64 lineBaseSize= 0;

        // the line size with endl . (depends on platform)
        quint64 lineSize    = 0;

        //  Loop of genom file and compute for each chromosom :
        //        name	baseCount	firstOffset	lineBaseSize	lineSize
        //        ex:
        //        chr1	550	6	50	51
        //        chr2	550	573	50	51

        while (!file.atEnd())
        {
            QByteArray line = file.readLine();

            // output line to the stream
            if ( line.startsWith(">") && lineNumber != 0)
                stream<<name<<"\t"<<baseCount<<"\t"<<firstOffset<<"\t"<<lineBaseSize<<"\t"<<lineSize<<"\n";

            // Detect line header
            //-------------------------------------
            if (line.startsWith(">"))
            {
                name        = line.right(line.size()-1).simplified();
                firstOffset = file.pos();
                baseCount   = 0;
            }
            // Otherwise count base
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

    qDebug()<<"sequences created";

    return true;
}

bool FastaDataModel::isValid()
{
    if (!QFile::exists(mFilename)){
        qDebug()<<"file doesn't exists";
        return false;
    }

    if (!QFile::exists(mIndexFilename)){
        qDebug()<<"index doesn't exists";
        return false;
    }

    return true;

}

void FastaDataModel::setQuery(const QString &chromosom, quint64 start, quint64 end)
{

    if (!isValid())
        return;

    setLoading(true);

    // Load index
    // Read Index file and get param. see createIndex()
    QByteArray name;
    quint64 baseCount;
    quint64 firstOffset;
    quint64 lineBaseSize;
    quint64 lineSize ;

    QFile file(filename(IndexFile));
    if (file.open(QIODevice::ReadOnly))
    {
        // loop over index file and get params
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();

            QByteArrayList list = line.split('\t');
            name = list[0];
            // get params only for the chromosom query
            if (name == chromosom.toUtf8())
            {
                baseCount    = list[1].toInt();
                firstOffset  = list[2].toInt();
                lineBaseSize = list[3].toInt();
                lineSize     = list[4].simplified().toInt();
                break;
            }
        }

        file.close();
        // Now read Original file and make random access memory

        QFile file(filename(SequenceFile));
        if (file.open(QIODevice::ReadOnly))
        {

            // Get lineNumber of position. They are lineNumber "\n" to avoid
            int lineNumber = start / lineBaseSize;

            // from the first offset, go to pos and avoid \n by adding lineNumber
            file.seek(firstOffset + start + lineNumber);
            // Now lets start to read base per base !
            int count = 0;
            QByteArray seq;
            while (count < end-start )
            {
                char base;
                file.read(&base,1);

                // detect out of range
                if (start + count >= baseCount){
                    qDebug()<<Q_FUNC_INFO<<QString("Feature (%1-%2) out of range").arg(start).arg(end);
                    break;
                }

                // avoid \n when reading
                if (base != '\n'){
                    ++count;
                    seq.append(base);
                }
            }
            emit sequenceReceived(Sequence(seq));

        }
    }
    setLoading(false);
}

}} // end namespace
