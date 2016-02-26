#ifndef BIGBROWSER_H
#define BIGBROWSER_H

#include <QObject>

class BigBrowser : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief singleton instance
     * \return instance of BigBrowser
     */
    BigBrowser * i();

    /*!
     * \brief databasePath
     * \return return location where all data are stored
     */
    QString databasePath();




private:
    explicit BigBrowser(QObject *parent = 0);

    static BigBrowser * mInstance;


};

#endif // BIGBROWSER_H
