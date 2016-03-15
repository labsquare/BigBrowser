#ifndef NUCLEOTIDALPHABET_H
#define NUCLEOTIDALPHABET_H
#include "alphabet.h"
#include <QHash>
#include <QVector>

namespace big{
namespace core {
class NucleotidAlphabet : public Alphabet
{
private:
    NucleotidAlphabet();

public:

    static QString name(unsigned char letter);
    static unsigned char complement(unsigned char letter);




protected:
    void initNames();
    void initComplements();


private:
    QHash<unsigned char, QString> mNames;
    QVector <unsigned char> mTables;

    static NucleotidAlphabet *mInstance;


};

}} // namespace

#endif // NUCLEOTIDALPHABET_H
