#ifndef SEQUENCE_H
#define SEQUENCE_H

/* std include */
#include <iostream>

/* Qt include*/
#include <QByteArray>
#include <QChar>

namespace big {
    namespace core {
	namespace sequence {
	    /*!
	     * \brief Transform
	     * Used for perform some biological operation on sequence
	     */
	    class Transform
	    {
	    private:

		Transform();

	    public:

		/*!
		 * \brief instance
		 *
		 * Get a pointer on Transform object
		 *
		 * \return Transform pointer
		 */
		static Transform* instance();

		/*!
		 * \brief complement
		 * \return the complement sequence
		 */
		template<typename SOURCE>
		    SOURCE complement(SOURCE src)
		{
		    SOURCE c = SOURCE(src.length(), 'A');

		    auto src_begin = src.begin();
		    auto src_end = src.end();
		    auto c_begin = c.begin();
		    for(; src_begin <= src_end; src_begin++, c_begin++)
		    {
			*c_begin = this->complement(*src_begin);
		    }

		    return c;
		}

		/*!
		 * \brief complement
		 *
		 * Return the complement of nucleotide.
		 *
		 * For Adenine return always Thymine no Uracil.
		 * If IUPAC alphabet is use in sequence we return the same letter.
		 * Case is keep
		 *
		 * If letter is not in IUPAC Alphabet behavior of function is
		 * undefine
		 *
		 * \param nucleotide
		 * \return the complement of original nucleotide
		 */
		char complement(char nuc);
		QChar complement(QChar& nuc);

		/*!
		 * \brief reverse
		 * \return the reverse sequence
		 */
		template<typename SOURCE>
		    SOURCE reverse(SOURCE src)
		{
		    SOURCE c = SOURCE(src.length(), 'A');

		    auto src_begin = src.begin();
		    auto src_end = src.end(); src_end--;
		    auto c_begin = c.begin();
		    auto c_end = c.end(); c_end--;
		    for(; src_begin <= src_end; src_begin++, src_end--, c_begin++, c_end--)
		    {
			*c_begin = *src_end;
			*c_end = *src_begin;
		    }

		    return c;
		}

		/*!
		 * \brief reverseComplement
		 * \return the reverse complement sequence
		 */
		template<typename SOURCE>
		    SOURCE reverseComplement(SOURCE src)
		{
		    SOURCE c = SOURCE(src.length(), 'A');

		    auto src_begin = src.begin();
		    auto src_end = src.end(); src_end--;
		    auto c_begin = c.begin();
		    auto c_end = c.end(); c_end--;
		    for(; src_begin <= src_end; src_begin++, src_end--, c_begin++, c_end--)
		    {
			*c_begin = this->complement(*src_end);
			*c_end = this->complement(*src_begin);
		    }

		    return c;
		}

	    private:

		static Transform* m_instance;
		unsigned char mComplement[122];
	    };


	    template<typename SEQ>
		SEQ transcribe(SEQ &orig)
	    {
		SEQ next();
		next.sequence = orig.sequence;
	        
		return next;
	    }

	    template<typename SEQ>
	        SEQ backTranscribe(SEQ &orig)
	    {
	        SEQ next;

		next = orig;

		return next;
	    }

	    template<typename SEQ>
		SEQ translate(SEQ &orig)
	    {
	        SEQ next;

	        next = orig;

		return next;
	    }
	    
	    template<typename SEQ>
	        SEQ complement(SEQ &orig)
	    {
	        SEQ next;

	        next = Transform::instance()->complement(orig);

		return next;
	    }

	    template<typename SEQ>
	        SEQ reverse(SEQ  &orig)
	    {
	        SEQ next;

	        next = Transform::instance()->reverse(orig);

		return next;
	    }

	    template<typename SEQ>
		SEQ reverseComplement(SEQ &orig)
	    {
	        SEQ next;

	        next = Transform::instance()->reverseComplement(orig);

		return next;
	    }
	} // end of namespace sequence

	/*!
	 * Definition of Sequence with specialisation of sequence::Base
	 */
	typedef QByteArray Sequence;

    } // end of namespace core
} // end of namespace big

#endif // SEQUENCE_H
