#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H
#include <QToolBar>
#include <QToolButton>
#include <QComboBox>
#include <QLineEdit>
namespace big {
class MainToolBar : public QToolBar
{
    Q_OBJECT
public:
    MainToolBar(QWidget * parent = 0);


private:
    QComboBox * mGenomComboBox;
    QLineEdit * mLocationEdit;


};
}
#endif // MAINTOOLBAR_H
