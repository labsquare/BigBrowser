#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <QtCore>


namespace big {
namespace core {

class Sequence : public QByteArray
{
public:
    enum Type {
        Adn     = 0x01,
        Arn     = 0x02,
        Protein = 0x03
    };

    enum Strand {
        Forward = 0x01, // 5' to 3'
        Reverse = 0x02  // 3' to 5'
    };

    Sequence(const char *data);

    Sequence complement() const;
    Sequence translate() const;
    Sequence transcribe() const;

    void reverse();


    QString name() const;
    void setName(const QString &name);

    Strand strand() const;
    void setStrand(const Strand &strand);

private:
    // do not use pointer. Not virtual destructor
    QString mName;
    Strand mStrand;

};

} // end of namespace core
} // end of namespace big

#endif // SEQUENCE_H
