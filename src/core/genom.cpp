#include "genom.h"
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
namespace big {
namespace core {
Genom::Genom(const QString &path)
    :mDir(path)
{
    mName             = mDir.dirName();
    mSeqFilename      = mDir.filePath(mName+".fa");
    mIndexFilename    = mDir.filePath(mName+".fa.fai");
    mCytobandFilename = mDir.filePath(mName+".cytoBand");

    loadChromosoms();

}

int Genom::chromosomCount()
{
    return mChromosoms.count();
}

int Genom::chromosomLength(const QString &chromosom)
{
    // return chromosom length . -1 if name is wrong
    return mChromosoms.value(chromosom.toUtf8(), -1);

}

RegionList Genom::cytoBand(const QString &chromosom)
{
    // create cytoband region list according chromosom name
    RegionList regions;

    if (hasCytoband())
    {
        CytobandReader reader(filename(CytobandFile));

        if (reader.open(QIODevice::ReadOnly)){
            while (reader.next())
            {
                if (reader.region().chromosom() == chromosom)
                    regions.append(reader.region());
            }
        }
    }

    return regions;
}

Sequence Genom::sequence(const QString &chromosom, quint64 pos, quint64 length)
{
    // This function generate a Sequence object using a fai index file

    if (!hasIndex())
    {
        qDebug()<<Q_FUNC_INFO<<"fai index has not been created..";
        return Sequence();
    }

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
            int lineNumber = pos / lineBaseSize;

            // from the first offset, go to pos and avoid \n by adding lineNumber
            file.seek(firstOffset + pos + lineNumber);
            // Now lets start to read base per base !
            int count = 0;
            QByteArray seq;
            while (count < length )
            {
                char base;
                file.read(&base,1);

                // detect out of range
                if (pos + count >= baseCount){
                 qDebug()<<Q_FUNC_INFO<<QString("Feature (%1-%2) out of range").arg(pos).arg(pos+length);
                    break;
                }

                // avoid \n when reading
                if (base != '\n'){
                    ++count;
                    seq.append(base);
                }
            }
            return Sequence(seq);
        }
    }
    return Sequence();
}

const QString &Genom::name() const
{
    return mName;
}

const QString &Genom::filename(Genom::FileType type) const
{
    if (type == SequenceFile)
        return mSeqFilename;

    if (type == IndexFile)
        return mIndexFilename;

    if ( type == CytobandFile)
        return mCytobandFilename;

    return QString();
}

bool Genom::isValid()
{
    // Genom is valid if genom, index and cytoband exists
    return hasIndex() &&
            hasCytoband() &&
            QFile::exists(filename(SequenceFile));
}

bool Genom::hasIndex()
{
    qDebug()<<filename(IndexFile);
    return QFile::exists(filename(IndexFile));
}

bool Genom::hasCytoband()
{
    return QFile::exists(filename(CytobandFile));

}

bool Genom::createIndex()
{
    // The purpose of this function is to create an index file <filename.fa>.fai following the rule
    // from http://www.htslib.org/doc/faidx.html

    // This is the genome file
    QFile file(filename(SequenceFile));

    // This is the index file to be generated
    QFile outputFile(filename(IndexFile));

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
        int firstOffset = 0;

        // the line size without endl (depends on platform)
        int lineBaseSize= 0;

        // the line size with endl . (depends on platform)
        int lineSize    = 0;

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
    return true;
}

void Genom::loadChromosoms()
{
    if (isValid())
    {
        QFile file(filename(IndexFile));
        if (file.open(QIODevice::ReadOnly))
        {
            mChromosoms.clear();
            while (!file.atEnd())
            {
                QByteArrayList list =  file.readLine().split('\t');
                // get chromosom name at 0 , and chromosome size at 1
                mChromosoms[list.at(0)] = list.at(1).toInt();
            }
        }
    }
}

}}
