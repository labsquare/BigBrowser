#ifndef NUCLEOTIDALPHABET_H
#define NUCLEOTIDALPHABET_H
#include "alphabet.h"
#include <QHash>
#include <QVector>
#include <QMutexLocker>
namespace big{
namespace core {
class NucleotidAlphabet : public Alphabet
{
private:
    NucleotidAlphabet();

public:

    static QString name(unsigned char letter);
    static unsigned char complement(unsigned char letter);


    static NucleotidAlphabet * i();




private:

    void initNames();
    void initComplements();

    QHash<unsigned char, QString> mNames;
     QVector<unsigned char> mTables;
    static NucleotidAlphabet *mInstance;


};

}} // namespace

#endif // NUCLEOTIDALPHABET_H
