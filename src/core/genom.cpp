#include "genom.h"
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
namespace big {
namespace core {
Genom::Genom()
    :mDevice(0)
{

}

Genom::Genom(QIODevice * device)
    :mDevice(0)
{
    load(device);
}

Genom::Genom(const QString& filename)
    :mDevice(0)
{
    load(filename);
}

Genom::~Genom()
{
    delete mDevice;
    mChromosomsBands.clear();
    mChromosomsSize.clear();
}



void Genom::load(QIODevice * device)
{
    mDevice = device;
    mZip.setIoDevice(device);
    mZip.open(QuaZip::mdUnzip);
    QuaZipFile file(&mZip);

    // first load property data
    mZip.setCurrentFile("property.txt");
    loadProperty(&file);

    if (mProperties.contains("cytobandFile"))
    {
        mZip.setCurrentFile(mProperties["cytobandFile"]);
        loadCytoBand(&file);
    }
    mZip.close();

}

void Genom::load(const QString &filename)
{
    if (mDevice)
        delete mDevice;

    QFile * file = new QFile(filename);
    if (file->exists())
        load(file);
    else
        qDebug()<<Q_FUNC_INFO<<filename<<" doesn't exists";

}

void Genom::loadCytoBand(QIODevice *device)
{
    if (device->open(QIODevice::ReadOnly))
    {
        mChromosomsBands.clear();
        mChromosomsSize.clear();
        CytobandReader reader(device);
        while (reader.next())
        {
            Region region = reader.region();
            // Create chromosom Size hash
            if (!mChromosomsSize.keys().contains(region.chromosom())){
                mChromosomsSize.insert(region.chromosom(), 0);
                mChromosomsBands.insert(region.chromosom(), RegionList());
                mChromosomsBands[region.chromosom()].append(region);

            }
            else {
                mChromosomsSize[region.chromosom()] = qMax(mChromosomsSize.value(region.chromosom()), region.end());
                mChromosomsBands[region.chromosom()].append(region);
            }
        }
        device->close();

    }

}

void Genom::loadProperty(QIODevice *device)
{
    if (device->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device);

        while (!stream.atEnd())
        {
            QStringList line = stream.readLine().simplified().split("=");
            if (line.size() == 2)
                mProperties.insert(line[0],line[1]);
        }

        device->close();


    }
}

int Genom::chromosomCount()
{
    return mChromosomsSize.count();
}

int Genom::chromosomLength(const QString &chromosom)
{
    return mChromosomsSize.value(chromosom,-1);
}

QStringList Genom::chromosoms()
{
    return mChromosomsSize.keys();
}

const RegionList Genom::chromosomBand(const QString &chromosom) const
{
    return mChromosomsBands.value(chromosom);
}

Sequence Genom::sequence(const QString &chromosom, quint64 pos, quint64 length)
{
    //    // This function generate a Sequence object using a fai index file

    //    if (!hasIndex())
    //    {
    //        qDebug()<<Q_FUNC_INFO<<"fai index has not been created..";
    //        return Sequence();
    //    }

    //    // Load index
    //    // Read Index file and get param. see createIndex()
    //    QByteArray name;
    //    quint64 baseCount;
    //    quint64 firstOffset;
    //    quint64 lineBaseSize;
    //    quint64 lineSize ;

    //    QFile file(filename(IndexFile));
    //    if (file.open(QIODevice::ReadOnly))
    //    {
    //        // loop over index file and get params
    //        while (!file.atEnd())
    //        {
    //            QByteArray line = file.readLine();

    //            QByteArrayList list = line.split('\t');
    //            name = list[0];
    //            // get params only for the chromosom query
    //            if (name == chromosom.toUtf8())
    //            {
    //                baseCount    = list[1].toInt();
    //                firstOffset  = list[2].toInt();
    //                lineBaseSize = list[3].toInt();
    //                lineSize     = list[4].simplified().toInt();
    //                break;
    //            }
    //        }

    //        file.close();
    //        // Now read Original file and make random access memory

    //        QFile file(filename(SequenceFile));
    //        if (file.open(QIODevice::ReadOnly))
    //        {

    //            // Get lineNumber of position. They are lineNumber "\n" to avoid
    //            int lineNumber = pos / lineBaseSize;

    //            // from the first offset, go to pos and avoid \n by adding lineNumber
    //            file.seek(firstOffset + pos + lineNumber);
    //            // Now lets start to read base per base !
    //            int count = 0;
    //            QByteArray seq;
    //            while (count < length )
    //            {
    //                char base;
    //                file.read(&base,1);

    //                // detect out of range
    //                if (pos + count >= baseCount){
    //                    qDebug()<<Q_FUNC_INFO<<QString("Feature (%1-%2) out of range").arg(pos).arg(pos+length);
    //                    break;
    //                }

    //                // avoid \n when reading
    //                if (base != '\n'){
    //                    ++count;
    //                    seq.append(base);
    //                }
    //            }
    //            return Sequence(seq);
    //        }
    //    }
    //    return Sequence();
}

QString Genom::name() const
{
    return mProperties["name"];
}

QString Genom::id() const
{
    return mProperties["id"];
}



bool Genom::isValid()
{
    mZip.open(QuaZip::mdUnzip);
    bool success=mZip.getZipError() == UNZ_OK & mZip.getFileNameList().contains("property.txt");
    mZip.close();
    return success;

}

//bool Genom::hasIndex()
//{
//    //    qDebug()<<filename(IndexFile);
//    //    return QFile::exists(filename(IndexFile));
//}

bool Genom::hasCytoband()
{
    return !mChromosomsBands.isEmpty();
}

//bool Genom::createIndex()
//{
//    // The purpose of this function is to create an index file <filename.fa>.fai following the rule
//    // from http://www.htslib.org/doc/faidx.html

//    // This is the genome file
//    QFile file(filename(SequenceFile));

//    // This is the index file to be generated
//    QFile outputFile(filename(IndexFile));

//    // Create a text stream to easily read inside the genome file
//    QTextStream stream(&outputFile);

//    if (file.open(QIODevice::ReadOnly))
//    {
//        // How many line of seq for chromosom X
//        quint64 lineNumber = 0;

//        // How many base of seq for chromosom x
//        quint64 baseCount  = 0;

//        // The name of chromosome x : eg  chr3
//        QByteArray name;

//        // The byte offset where the sequence start for chromosom X
//        int firstOffset = 0;

//        // the line size without endl (depends on platform)
//        int lineBaseSize= 0;

//        // the line size with endl . (depends on platform)
//        int lineSize    = 0;

//        //  Loop of genom file and compute for each chromosom :
//        //        name	baseCount	firstOffset	lineBaseSize	lineSize
//        //        ex:
//        //        chr1	550	6	50	51
//        //        chr2	550	573	50	51

//        while (!file.atEnd())
//        {
//            QByteArray line = file.readLine();

//            // output line to the stream
//            if ( line.startsWith(">") && lineNumber != 0)
//                stream<<name<<"\t"<<baseCount<<"\t"<<firstOffset<<"\t"<<lineBaseSize<<"\t"<<lineSize<<"\n";

//            // Detect line header
//            //-------------------------------------
//            if (line.startsWith(">"))
//            {
//                name        = line.right(line.size()-1).simplified();
//                firstOffset = file.pos();
//            }
//            // Otherwise count base
//            //-------------------------------------
//            else {
//                baseCount += line.simplified().size();
//                if (!lineSize){
//                    lineBaseSize = line.simplified().size();
//                    lineSize     =  line.size();
//                }
//            }

//            ++lineNumber;
//        }
//        // last line ...
//        stream<<name<<"\t"<<baseCount<<"\t"<<firstOffset<<"\t"<<lineBaseSize<<"\t"<<lineSize<<"\n";
//    }
//    file.close();

//    // Write results to index file
//    if (outputFile.open(QIODevice::WriteOnly))
//    {
//        stream.flush();
//        outputFile.close();

//    }
//    return true;
//}



}}
