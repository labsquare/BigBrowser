
/* Project include */
#include "sequence.h"

namespace big {

    namespace core {

	namespace sequence
	{
	    Transform* Transform::m_instance = nullptr;

	    Transform::Transform()
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
	
	    Transform* Transform::instance()
	    {
		if(Transform::m_instance == nullptr)
		{
		    Transform::m_instance = new Transform();
		}

		return Transform::m_instance;
	    }

	    char Transform::complement(char nuc)
	    {
		return this->mComplement[nuc];
	    }

	    QChar Transform::complement(QChar& nuc)
	    {
		return this->complement(nuc.toLatin1());
	    }
	} // end of namespace sequence
    } // end of namespace core
} // end of namespace big

















