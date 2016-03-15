#include "nucleotidalphabet.h"
namespace big{
namespace core {
NucleotidAlphabet::NucleotidAlphabet()
{
    mletters = {{'-',"gap"},
                {'.',"gap"},
                {'A',"Adenine"},
                {'B',"C or G or T"},
                {'C',"Cytosine"},
                {'D',"A or G or T"},
                {'G',"Guanine"},
                {'H',"A or C or T"},
                {'K',"G or T"},
                {'M',"A or C"},
                {'N',"any base"},
                {'R',"A or G"},
                {'S',"G or C"},
                {'T',"Thymine"},
                {'U',"Uracil"},
                {'V',"A or C or G"},
                {'W',"A or T"},
                {'Y',"C or G"},
               };
}



}} // namespace
