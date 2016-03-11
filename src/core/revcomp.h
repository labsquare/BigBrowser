#pragma once

namespace big
{
    namespace core
    {
	class RevComp
	{
	private:
	    
	    RevComp();

	public:

	    /*!
	     * \brief instance
	     *
	     * Get a pointer on RevComp object
	     * 
	     * \return RevComp pointer
	     */
	    static RevComp* instance();

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
	    unsigned char complement(unsigned char nuc);	    

	    /*!
	     * \brief reverse
	     * \return the reverse sequence
	     */
	    template<typename OUT, typename SOURCE>
		OUT reverse(SOURCE src)
	    {
		OUT c = OUT(src.length(), 'A');

		auto src_begin = src.begin();
		auto src_end = src.end();
		auto c_begin = c.begin();
		auto c_end = c.end();
		for(; src_begin <= src_end; src_begin++, src_end--, c_begin++, c_end--)
		{
	            *c_begin = *src_begin;
		    *c_end = *src_end;
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
		auto src_end = src.end();
		auto c_begin = c.begin();
		auto c_end = c.end();
		for(; src_begin <= src_end; src_begin++, src_end--, c_begin++, c_end--)
		{
		    *c_begin = this->complement(*src_begin);
		    *c_end = this->complement(*src_end);
		}

		return c;
	    }

	private:

	    static RevComp* m_instance;
	    unsigned char mComplement[122];
	};
    } // end of namespace core
} // end of namespace big










