#ifndef PROTEINALPHABET_H
#define PROTEINALPHABET_H
#include "alphabet.h"
namespace big {
namespace core {
/*! \class ProteinAlphabet
 *  \brief static class to get aminoAcid name and translation from codon
 *  \see Sequence
 */
class ProteinAlphabet : public Alphabet
{
private:
    ProteinAlphabet();



public:
    void initGeneticCode();
    void initNames();

    static QString name(unsigned char iupac);
    static QString shortName(unsigned char iupac);
    static unsigned char codonToAA(const QByteArray& codon);


    static ProteinAlphabet* i();


private:
    static ProteinAlphabet *mInstance;
    // codon to AA
    QHash<unsigned char, QPair<QString,QString> > mNames;
    QHash<QByteArray, unsigned char> mCodes;



};



}} // end namespace

#endif // PROTEINALPHABET_H
