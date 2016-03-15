
/* Project include */
#include "sequence.h"

namespace big {

namespace core {

Sequence::Sequence(const char *data)
    :QByteArray(data)
{

}

Sequence::Sequence()
    :QByteArray()
{

}

Sequence Sequence::complement() const
{
    return Sequence();
}

Sequence Sequence::translate() const
{
    return Sequence();
}

Sequence Sequence::transcribe() const
{

    return Sequence();
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



} // end of namespace core
} // end of namespace big

















