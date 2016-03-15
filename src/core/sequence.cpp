
/* Project include */
#include "sequence.h"

namespace big {

namespace core {

Sequence::Sequence(const char *data)
    :mArray(data),mType(Adn), mStrand(Forward)
{

}

Sequence::Sequence(const QByteArray &bytes)
    :mArray(bytes),mType(Adn), mStrand(Forward)
{
}

Sequence::Sequence()
    :mArray(),mType(Adn), mStrand(Forward)
{
}

Sequence Sequence::complement() const
{
    // @Natir

    QByteArray c;
    c.fill('A', count());

    auto src_begin = byteArray().begin();
    auto src_end = byteArray().end();
    auto c_begin = c.begin();
    for(; src_begin <= src_end; src_begin++, c_begin++)
    {
        *c_begin = NucleotidAlphabet::complement(*src_begin);
    }

    return Sequence(c);
}

Sequence Sequence::translate() const
{
    // @Natir


    return Sequence();
}

Sequence Sequence::transcribe() const
{
    // @Natir
    QByteArray c = byteArray();
    Sequence newSeq = Sequence(c);

    newSeq.setType(Arn);
    return newSeq;
}

Sequence Sequence::reverse() const
{
    QByteArray c;
    c.fill('A', count());

    auto src_begin = byteArray().begin();
    auto src_end = byteArray().end(); src_end--;
    auto c_begin = c.begin();
    auto c_end = c.end(); c_end--;
    for(; src_begin <= src_end; src_begin++, src_end--, c_begin++, c_end--)
    {
        *c_begin = *src_end;
        *c_end = *src_begin;
    }

    Sequence newSeq = Sequence(c);
    newSeq.setStrand(strand() == Forward ? Reverse : Forward);

    return newSeq;
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

















