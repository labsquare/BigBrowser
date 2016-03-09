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
    const QString& genomPath() const;
    void setGenomPath(const QString& path);
    const QString& annotationPath() const;
    void setAnnotationPath(const QString& path);
    void setDefaultPath() ;
    QStringList avaibleGenoms() const;






protected:

private:
    explicit App(QObject *parent = 0);
    static App * mInstance;
    QString mGenomPath;
    QString mAnnotationPath;


};
}}
#endif // BIGBROWSER_H
