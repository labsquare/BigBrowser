#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H
#include <QToolBar>
#include <QToolButton>
#include <QComboBox>
#include <QLineEdit>
#include "genom.h"

namespace big {
using namespace core;

namespace gui {
class MainToolBar : public QToolBar
{
    Q_OBJECT
public:
    MainToolBar(QWidget * parent = 0);
    //    void setSelector(Selector * selector);


    //protected Q_SLOTS:
    //void locationChanged();
    //void updateLocation();

    //Q_SIGNALS:
    //    void chromosomeChanged(const QString& chromosom);

protected:
    void createActions();
    void loadChromosom();




private:
    QComboBox * mGenomComboBox;
    QComboBox * mChromosomComboBox;
    QLineEdit * mLocationEdit;
    Genom * mGenom;


};
}}
#endif // MAINTOOLBAR_H
