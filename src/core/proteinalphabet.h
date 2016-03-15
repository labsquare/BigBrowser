#ifndef PROTEINALPHABET_H
#define PROTEINALPHABET_H
#include "alphabet.h"
namespace big {
namespace core {
class ProteinAlphabet : public Alphabet
{
private:
    ProteinAlphabet();



public:
    void initGeneticCode();


private:
    static ProteinAlphabet *mInstance;



};



}} // end namespace

#endif // PROTEINALPHABET_H
