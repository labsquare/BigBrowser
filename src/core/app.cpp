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

QStringList App::avaibleGenoms() const
{
    QStringList list;
    QDir dir(databasePath()+QDir::separator()+"genom");
    foreach (QFileInfo info, dir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot))
    {
        list.append(info.baseName());
    }

    return list;
}

QString App::genomPath(const QString &name)
{
    return databasePath()+QDir::separator()+"genom"+QDir::separator()+name;

}

App::App(QObject *parent) :
    QObject(parent)
{
    mGenom = new Genom();
}

}}
