#include "proteinalphabet.h"
namespace big {
namespace core {

ProteinAlphabet * ProteinAlphabet::mInstance = new ProteinAlphabet;

ProteinAlphabet::ProteinAlphabet()
{
    initGeneticCode();
}



void ProteinAlphabet::initGeneticCode()
{

}


}} // end namespace
