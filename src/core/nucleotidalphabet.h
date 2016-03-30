#ifndef NUCLEOTIDALPHABET_H
#define NUCLEOTIDALPHABET_H
#include "alphabet.h"
#include <QHash>
#include <QVector>
#include <QMutexLocker>
namespace big{
namespace core {
/*! \class NucleotidAlphabet
 *  \brief static class to get base name and get complement
 *  \see Sequence
 */
class NucleotidAlphabet : public Alphabet
{
private:
    NucleotidAlphabet();

public:

    static QString name(unsigned char iupac);
    static unsigned char complement(unsigned char iupac);


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
