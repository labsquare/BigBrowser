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
class SelectToolBar : public QToolBar
{
    Q_OBJECT
public:
    SelectToolBar(QWidget * parent = 0);
    /*!
     * \brief setGenom
     * \param genom
     */
    void setGenom(Genom * genom);

    /*!
     * \brief reset
     * Load avaible genom and set the region edit to null
     */
    void reset();



public Q_SLOTS:
    /*!
     * \brief setSelection
     * Mandatory slot methods working with selectionRouter
     * \param region
     */
    void setSelection(const Region& region);

Q_SIGNALS:
    /*!
     * \brief selectionChanged
     * Mandatory signals methods working with selectionRouter
     * \param region
     */
    void selectionChanged(const Region& region);

    /*!
     * \brief genomChanged
     * emit when genom has been changed
     * \param name
     */
    void genomChanged(const QString& name);

protected:
    void loadAvaibleGenom();
    void createActions();

protected Q_SLOTS:
    void locationEditChanged();
    void chromosomChanged();
    void genomComboBoxChanged();


private:
    QComboBox * mGenomComboBox;
    QComboBox * mChromosomComboBox;
    QLineEdit * mLocationEdit;
    Genom * mGenom;


};
}}
#endif // MAINTOOLBAR_H
