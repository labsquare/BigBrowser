
/* Project include */
#include "sequence.h"

namespace big {

namespace core {

QVector<unsigned char> Sequence::complementTable = Sequence::createComplementTable();

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
        *c_begin = Sequence::baseToComplement(*src_begin);
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

unsigned char Sequence::baseToComplement(unsigned char base) const
{
    return Sequence::complementTable.at(base);

}

QVector <unsigned char> Sequence::createComplementTable()
{
    QVector<unsigned char> tables(122);
    tables.fill(' '); // avoid error
    tables['-'] = '-'; // gap
    tables['.'] = '.'; // gap
    tables['A'] = 'T'; // Adenine
    tables['B'] = 'B'; // C or G or T
    tables['C'] = 'G'; // Cytosine
    tables['D'] = 'D'; // A or G or T
    tables['G'] = 'C'; // Guanine
    tables['H'] = 'H'; // A or C or T
    tables['K'] = 'K'; // G or T
    tables['M'] = 'M'; // A or C
    tables['N'] = 'N'; // any base
    tables['R'] = 'R'; // A or G
    tables['S'] = 'S'; // G or C
    tables['T'] = 'A'; // Thymine
    tables['U'] = 'A'; // Uracil
    tables['V'] = 'V'; // A or C or G
    tables['W'] = 'W'; // A or T
    tables['Y'] = 'Y'; // C or G
    tables['a'] = 't'; // Adenine
    tables['b'] = 'b'; // C or G or T
    tables['c'] = 'g'; // Cytosine
    tables['d'] = 'd'; // A or G or T
    tables['g'] = 'c'; // Guanine
    tables['h'] = 'h'; // A or C or T
    tables['k'] = 'k'; // G or T
    tables['m'] = 'm'; // A or C
    tables['n'] = 'n'; // any base
    tables['r'] = 'r'; // A or G
    tables['s'] = 's'; // G or C
    tables['t'] = 'a'; // Thymine
    tables['u'] = 'a'; // Uracil
    tables['v'] = 'v'; // A or C or G
    tables['w'] = 'w'; // A or T
    tables['y'] = 'y'; // C or G

    return tables;

}


} // end of namespace core
} // end of namespace big

















