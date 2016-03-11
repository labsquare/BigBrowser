
/* project include */
#include "revcomp.h"

namespace big
{
    namespace core
    {
	RevComp* RevComp::m_instance = nullptr;

	RevComp::RevComp()
	{
	    this->mComplement['-'] = '-'; // gap
	    this->mComplement['.'] = '.'; // gap
	    this->mComplement['A'] = 'T'; // Adenine
	    this->mComplement['B'] = 'B'; // C or G or T
	    this->mComplement['C'] = 'G'; // Cytosine
	    this->mComplement['D'] = 'D'; // A or G or T
	    this->mComplement['G'] = 'C'; // Guanine
	    this->mComplement['H'] = 'H'; // A or C or T
	    this->mComplement['K'] = 'K'; // G or T
	    this->mComplement['M'] = 'M'; // A or C
	    this->mComplement['N'] = 'N'; // any base
	    this->mComplement['R'] = 'R'; // A or G
	    this->mComplement['S'] = 'S'; // G or C
	    this->mComplement['T'] = 'A'; // Thymine
	    this->mComplement['U'] = 'A'; // Uracil
	    this->mComplement['V'] = 'V'; // A or C or G
	    this->mComplement['W'] = 'W'; // A or T
	    this->mComplement['Y'] = 'Y'; // C or G
	    this->mComplement['a'] = 't'; // Adenine
	    this->mComplement['b'] = 'b'; // C or G or T
	    this->mComplement['c'] = 'g'; // Cytosine
	    this->mComplement['d'] = 'd'; // A or G or T
	    this->mComplement['g'] = 'c'; // Guanine
	    this->mComplement['h'] = 'h'; // A or C or T
	    this->mComplement['k'] = 'k'; // G or T
	    this->mComplement['m'] = 'm'; // A or C
	    this->mComplement['n'] = 'n'; // any base
	    this->mComplement['r'] = 'r'; // A or G
	    this->mComplement['s'] = 's'; // G or C
	    this->mComplement['t'] = 'a'; // Thymine
	    this->mComplement['u'] = 'a'; // Uracil
	    this->mComplement['v'] = 'v'; // A or C or G
	    this->mComplement['w'] = 'w'; // A or T
	    this->mComplement['y'] = 'y'; // C or G
	}
	
	RevComp* RevComp::instance()
	{
	    if(RevComp::m_instance == nullptr)
	    {
		RevComp::m_instance = new RevComp();
	    }

	    return RevComp::m_instance;
	}
    } // end of namespace core
} // end of namespace big
