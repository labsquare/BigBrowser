
/* Project include */
#include "sequence.h"

namespace big {
namespace core {

Sequence::Sequence(const char *data)
    :mArray(data), mStrand(Forward),mType(Dna)
{

}

Sequence::Sequence(const QByteArray &bytes)
    :mArray(bytes), mStrand(Forward),mType(Dna)
{
}

Sequence::Sequence()
    :mArray(), mStrand(Forward),mType(Dna)
{
}

Sequence::Sequence(const QByteArray& bytes, Strand strand, Type type)
    :mArray(bytes), mStrand(strand), mType(type)
{
}

Sequence Sequence::complement() const
{
    if (type() == Protein)
    {
        qWarning()<<"cannot complement a protein";
        return Sequence();
    }

    QByteArray c;
    c.fill('A', count());

    auto src_begin = byteArray().begin();
    auto src_end = byteArray().end();
    auto c_begin = c.begin();
    for(; src_begin <= src_end; src_begin++, c_begin++)
    {
        *c_begin = NucleotidAlphabet::complement(*src_begin);
    }

    Sequence newSeq(c);
    newSeq.setName(name());
    newSeq.setStrand(strand());
    newSeq.setType(type());

    return newSeq;
}

Sequence Sequence::translate() const
{
    if (type() == Protein)
    {
        qWarning()<<"cannot translate a protein";
        return Sequence();
    }

    QByteArray array;


    Sequence seq(array);
    seq.setStrand(strand());
    seq.setType(Protein);
    seq.setName(name());
    return seq;
}

Sequence Sequence::transcribe() const
{
    if (type() == Protein)
    {
        qWarning()<<"cannot transcribe a protein";
        return Sequence();
    }
    QByteArray c = byteArray();
    Sequence newSeq = Sequence(c);
    newSeq.setType(Rna);
    newSeq.setName(name());
    newSeq.setStrand(strand());
    return newSeq;
}

Sequence Sequence::reverse() const
{
    QByteArray c;
    c.fill('A', count());

    auto src_begin = this->byteArray().begin();
    auto src_end = this->byteArray().end(); src_end--;
    auto c_begin = c.begin();
    auto c_end = c.end(); c_end--;
    for(; src_begin <= src_end; src_begin++, src_end--, c_begin++, c_end--)
    {
        *c_begin = *src_end;
        *c_end = *src_begin;
    }

    Sequence newSeq = Sequence(c);
    newSeq.setStrand(strand() == Forward ? Reverse : Forward);
    newSeq.setType(type());
    newSeq.setName(name());
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

QString Sequence::typeName()
{
    switch ( type())
    {
    case Dna: return "dna";
    case Rna: return "rna";
    case Protein:return "protein";
    default : return "unknown";
    }
}

int Sequence::count() const
{
    return mArray.count();
}

int Sequence::length() const
{
    return mArray.length();
}

char Sequence::at(int index) const
{
    return mArray.at(index);
}

void Sequence::setByteArray(const QByteArray &array)
{
    mArray = array;
}

const QByteArray &Sequence::byteArray() const
{
    return mArray;
}

QString Sequence::toString() const
{
    return QString(mArray);
}

Sequence Sequence::subSequence(int position, int n) const
{
    return Sequence(this->mArray.mid(position, n), this->mStrand, this->mType);
}

float Sequence::gcPercent() const
{
    float gc = 0;
    for(auto it = this->mArray.begin(); it != this->mArray.end(); it++)
    {
        if(NucleotidAlphabet::isGorC(*it))
            gc++;
    }

    return gc/this->mArray.length();
}

void Sequence::append(char base)
{
    mArray.append(base);
}

} // end of namespace core
} // end of namespace big

















