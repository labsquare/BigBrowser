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
class SearchToolBar : public QToolBar
{
    Q_OBJECT
public:
    SearchToolBar(QWidget * parent = 0);
    //    void setSelector(Selector * selector);


public Q_SLOTS:
    void setGenom(Genom * genom);
    void setSelection(const QString& chromosom, quint64 start, quint64 end);




Q_SIGNALS:
    void selectionChanged(const QString& chromosom, quint64 start, quint64 end);


protected:
    void createActions();

protected Q_SLOTS:
    void locationEditChanged();
    void chromosomChanged();



private:
    QComboBox * mGenomComboBox;
    QComboBox * mChromosomComboBox;
    QLineEdit * mLocationEdit;
    Genom * mGenom;


};
}}
#endif // MAINTOOLBAR_H
