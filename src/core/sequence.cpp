
/* Project include */
#include "sequence.h"

namespace big {

namespace core {

Sequence::Sequence(const char *data)
    :mArray(data)
{

}

Sequence::Sequence()
    :mArray()
{

}

Sequence Sequence::complement() const
{
    // @Natir



    return Sequence();
}

Sequence Sequence::translate() const
{
    // @Natir


    return Sequence();
}

Sequence Sequence::transcribe() const
{
    // @Natir



    return Sequence();
}

void Sequence::reverse()
{




    setStrand( strand() == Forward ? Reverse : Forward);
}


QString Sequence::name() const
{
    return mName;
}

void Sequence::setName(const QString &name)
{
    mName = name;
}

Sequence::Strand Sequence::strand() const
{
    return mStrand;
}

void Sequence::setStrand(const Strand &strand)
{
    mStrand = strand;
}

Sequence::Type Sequence::type() const
{
    return mType;
}

void Sequence::setType(const Type &type)
{
    mType = type;
}

int Sequence::count() const
{
    return mArray.count();
}

const QByteArray &Sequence::byteArray() const
{
    return mArray;
}

QString Sequence::toString() const
{
 return QString(mArray);
}




} // end of namespace core
} // end of namespace big

















