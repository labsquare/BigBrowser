#include "app.h"
#include <QDir>
#include <QDebug>
#include <QStandardPaths>
namespace big {
namespace core {
App* App::mInstance = nullptr;

App* App::i()
{
    if (!mInstance)
        mInstance = new App();

    return mInstance;

}

const QString &App::databasePath() const
{
    return mDatabasePath;
}

void App::setDatabasePath(const QString &path)
{

    // Check Path. Create it if doesn't exists
    QDir dir(path);
    if (!dir.exists()){
        qDebug()<<Q_FUNC_INFO<<"database path doesn't exist. It has been created";
        if (!dir.mkpath(path))
            qDebug()<<Q_FUNC_INFO<<"cannot create path. Check your path";
        return;
    }

    mDatabasePath = path;

}

void App::setDefaultDatabasePath()
{
    // set default path to your home directory
    setDatabasePath(QDir::homePath() + QDir::separator() + ".bigbrowser");
}

void App::setCurrentGenom(const QString &genom)
{
    mCurrentGenom = genom;
}

const QString &App::currentGenom() const
{
    return mCurrentGenom;
}

QString App::currentGenomPath() const
{
return databasePath()+QDir::separator()+"genom"+QDir::separator()+currentGenom();
}

QString App::currentGenomFilePath(const QString &filename)
{
    return currentGenomPath()+QDir::separator()+filename;
}




App::App(QObject *parent) : QObject(parent)
{

}

}}
