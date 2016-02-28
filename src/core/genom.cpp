#include "genom.h"

namespace big {
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

bool Genom::hasIndex()
{
    return false;
}

void Genom::createIndex()
{




}

}
