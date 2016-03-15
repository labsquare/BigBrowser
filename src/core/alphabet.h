#ifndef ALPHABET_H
#define ALPHABET_H
#include <QtCore>
namespace big{
namespace core {

class Alphabet
{
public:
    Alphabet();

protected:
    // A - Adénine
    QHash<unsigned char, QString> mletters;

};


}} // end namespace
#endif // ALPHABET_H
