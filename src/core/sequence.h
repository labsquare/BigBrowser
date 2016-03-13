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
		template<typename OUT, typename SOURCE>
		    OUT complement(SOURCE src)
		{
		    OUT c = OUT(src.length(), 'A');

		    auto src_begin = src.begin();
		    auto src_end = src.end();
		    auto c_begin = c.begin();
		    for(; src_begin <= src_end; src_begin++, c_begin++)
		    {
			/* std::cout<<src_begin->toLatin1()<<std::endl; */
			*c_begin = this->complement(*src_begin);
			/* std::cout<<c_begin->toLatin1()<<std::endl; */
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
		unsigned char complement(unsigned char nuc);
		QChar complement(QChar& nuc);

		/*!
		 * \brief reverse
		 * \return the reverse sequence
		 */
		template<typename OUT, typename SOURCE>
		    OUT reverse(SOURCE src)
		{
		    OUT c = OUT(src.length(), 'A');

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
		template<typename OUT, typename SOURCE>
		    OUT reverseComplement(SOURCE src)
		{
		    OUT c = OUT(src.length(), 'A');

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

	    /*!
	     * \brief Type
	     * Type of Sequence
	     */
	    enum Type
	    {
		DNA,
		RNA,
		PROTINE
	    };

	    /*!
	     * \brief Base
	     * Definition of general sequence
	     */
	    template<typename SEQ, typename COMMENT, typename TYPE>
		struct Base
		{
		    SEQ sequence;
		    COMMENT comment;
		    TYPE type;
		};

	    template<typename SEQ, typename COMMENT>
		Base<SEQ, COMMENT, Type> transcribe(Base<SEQ, COMMENT, Type> &orig)
	    {
		Base<SEQ, COMMENT, Type> next;

		next.comment = orig.comment;

		if(orig.type != Type::DNA)
		{
		    next.type = orig.type;
		    next.sequence = orig.sequence;
		}
		else
		{
		    next.type = Type::RNA;
		    next.sequence = orig.sequence;
		}

		return next;
	    }

	    template<typename SEQ, typename COMMENT, typename TYPE>
		Base<SEQ, COMMENT, TYPE> backTranscribe(Base<SEQ, COMMENT, TYPE> &orig)
	    {
		Base<SEQ, COMMENT, Type> next;

		next.comment = orig.comment;

		if(orig.type != Type::RNA)
		{
		    next.type = orig.type;
		    next.sequence = orig.sequence;
		}
		else
		{
		    next.type = Type::DNA;
		    next.sequence = orig.sequence;
		}

		return next;
	    }

	    template<typename SEQ, typename COMMENT, typename TYPE>
		Base<SEQ, COMMENT, TYPE> translate(Base<SEQ, COMMENT, TYPE> &orig)
	    {
		Base<SEQ, COMMENT, Type> next;

		next.comment = orig.comment;
		next.type = orig.type;
		next.sequence = orig.sequence;

		return next;
	    }
	    
	    template<typename SEQ, typename COMMENT, typename TYPE>
		Base<SEQ, COMMENT, TYPE> complement(Base<SEQ, COMMENT, TYPE> &orig)
	    {
		Base<SEQ, COMMENT, Type> next;

		next.comment = orig.comment;
		next.type = orig.type;
		next.sequence = Transform::instance()->complement<SEQ, SEQ>(orig.sequence);

		return next;
	    }

	    template<typename SEQ, typename COMMENT, typename TYPE>
		Base<SEQ, COMMENT, TYPE> reverse(Base<SEQ, COMMENT, TYPE> &orig)
	    {
		Base<SEQ, COMMENT, Type> next;

		next.comment = orig.comment;
		next.type = orig.type;
		next.sequence = Transform::instance()->reverse<SEQ, SEQ>(orig.sequence);

		return next;
	    }

	    template<typename SEQ, typename COMMENT, typename TYPE>
		Base<SEQ, COMMENT, TYPE> reverseComplement(Base<SEQ, COMMENT, TYPE> &orig)
	    {
		Base<SEQ, COMMENT, Type> next;

		next.comment = orig.comment;
		next.type = orig.type;
		next.sequence = Transform::instance()->reverseComplement<SEQ, SEQ>(orig.sequence);

		return next;
	    }
	} // end of namespace sequence

	/*!
	 * Definition of Sequence with specialisation of sequence::Base
	 */
	typedef sequence::Base<QString, QString, sequence::Type> Sequence;

    } // end of namespace core
} // end of namespace big

#endif // SEQUENCE_H
