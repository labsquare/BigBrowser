#ifndef BIGBROWSER_H
#define BIGBROWSER_H

#include <QObject>
#include "genom.h"

namespace big {
namespace core {

/*!
 * \brief Singleton class containing database path acccessor and settings of the application
 */
class App : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief singleton instance
     * \return instance of BigBrowser
     */
    static App * i();

    /*!
     * \brief databasePath
     * \return return location where all data are stored
     */
    const QString& databasePath() const;
    void setDatabasePath(const QString& path);
    void setDefaultDatabasePath();

    /*!
     * \brief setCurrentGenom
     *
     * Set the current genom path according genom name and databasePath
     * \param genom is the folder name of genom from <DATABASE_PATH>/genom/
     */
    void setCurrentGenom(Genom * genom);
    void setCurrentGenom(const QString& name);
    Genom * currentGenom();



protected:

private:
    explicit App(QObject *parent = 0);
    static App * mInstance;
    QString mDatabasePath;
    QString mCurrentGenom;
    Genom * mGenom;


};
}}
#endif // BIGBROWSER_H
