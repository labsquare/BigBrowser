#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <QtCore>


namespace big {
namespace core {

class Sequence : public QByteArray
{
public:
    enum Type {
        ADN     = 0x01,
        ARN     = 0x02,
        PROTEIN = 0x03
    };

    Sequence(const char *data);

    void reverse();
    Sequence reversed() const;


    QString name() const;
    void setName(const QString &name);

private:
    // do not use pointer. Not virtual destructor
QString mName;


};

} // end of namespace core
} // end of namespace big

#endif // SEQUENCE_H
