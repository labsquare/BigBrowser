#ifndef BIGBROWSER_H
#define BIGBROWSER_H

#include <QObject>
namespace big {
namespace core {
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
    void setCurrentGenom(const QString& genom);
    const QString& currentGenom() const;
    QString currentGenomPath() const;

    /*!
     * \brief currentGenomFilePath
     *
     * Return full path of filename from genom folder
     * \param filename
     * \return
     */
    QString currentGenomFilePath(const QString& filename);

protected:

private:
    explicit App(QObject *parent = 0);
    static App * mInstance;

    QString mDatabasePath;
    QString mCurrentGenom;


};
}}
#endif // BIGBROWSER_H
