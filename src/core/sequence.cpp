
/* Project include */
#include "sequence.h"

namespace big {

namespace core {

Sequence::Sequence(const char *data)
    :QByteArray(data)
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

Strand Sequence::strand() const
{
    return mStrand;
}

void Sequence::setStrand(const Strand &strand)
{
    mStrand = strand;
}



} // end of namespace core
} // end of namespace big

















