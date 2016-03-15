
/* Project include */
#include "sequence.h"

namespace big {

namespace core {

Sequence::Sequence(const char *data)
    :QByteArray(data)
{

}

void Sequence::reverse()
{

}

Sequence Sequence::reversed() const
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



} // end of namespace core
} // end of namespace big

















