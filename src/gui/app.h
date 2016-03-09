#ifndef BIGBROWSER_H
#define BIGBROWSER_H

#include <QObject>
#include "QtAwesome.h"

namespace big {
namespace gui {

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
    static QtAwesome * awesome();

    /*!
     * \brief databasePath
     * \return return location where all data are stored
     */
    const QString& genomPath() const;
    QString genomPath(const QString& filename) const;
    void setGenomPath(const QString& path);
    const QString& annotationPath() const;
    void setAnnotationPath(const QString& path);
    void setDefaultPath() ;
    QStringList avaibleGenoms() const;

protected:

private:
    explicit App(QObject *parent = 0);
    static App * mInstance;
    static QtAwesome * mAwesome;
    QString mGenomPath;
    QString mAnnotationPath;


};
}}
#endif // BIGBROWSER_H
