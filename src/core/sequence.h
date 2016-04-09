#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QtCore>
#include <QDebug>
#include "nucleotidalphabet.h"
#include "proteinalphabet.h"

namespace big {
namespace core {
/*! \class Sequence
 * \brief DNA/RNA/Protein sequence
 *
 */
	class Sequence
	{
	public:
	    enum Type {
		Dna     = 0x01,
		Rna     = 0x02,
		Protein = 0x03
	    };

	    enum Strand {
		Forward = 0x01, // 5' to 3'
		Reverse = 0x02  // 3' to 5'
	    };

	    Sequence(const char *data);
	    Sequence(const QByteArray& bytes);
	    Sequence();
	    Sequence(const QByteArray& bytes, Strand strand, Type type);
    
	    Sequence complement() const;
	    Sequence translate() const;
	    Sequence transcribe() const;
	    Sequence reverse() const;

	    QString name() const;
	    void setName(const QString &name);

	    Strand strand() const;
	    void setStrand(const Strand &strand);

	    Type type() const;
	    void setType(const Type &type);

	    QString typeName();

	    int count() const;
        int length() const;
        char at(int index) const;

	    void setByteArray(const QByteArray& array);
	    const QByteArray& byteArray() const;
	    QString toString() const;

	    Sequence subSequence(int position, int n=-1) const;

	    float gcPercent() const;

        void append(char base);



	private:
	    // do not use pointer. Not virtual destructor
	    QByteArray mArray;
	    Strand mStrand;
	    Type mType;
	    QString mName;


	};

    } // end of namespace core
} // end of namespace big

#endif // SEQUENCE_H
