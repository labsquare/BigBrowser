#include "app.h"
#include <QDir>
#include <QDebug>
#include <QStandardPaths>
namespace big {
namespace gui {
App* App::mInstance = nullptr;
QtAwesome* App::mAwesome  = nullptr;
App* App::i()
{
    if (!mInstance)
        mInstance = new App();

    return mInstance;

}

QtAwesome *App::awesome()
{
    if (!mAwesome){
        mAwesome = new QtAwesome();
        mAwesome->initFontAwesome();
    }
    return mAwesome;
}

const QString &App::genomPath() const
{
    return mGenomPath;
}

QString App::genomPath(const QString &filename) const
{
    return genomPath() + QDir::separator() + filename;
}

void App::setGenomPath(const QString &path)
{
    mGenomPath = path;
}

const QString &App::annotationPath() const
{
    return mAnnotationPath;
}

void App::setAnnotationPath(const QString &path)
{
    mAnnotationPath = path;
}

void App::setDefaultPath()
{
    QString basePath   = QDir::homePath() + QDir::separator() + "bigbrowser";
    QString genom      = basePath + QDir::separator() + "genome";
    QString annotation = basePath + QDir::separator() + "annotation";

    QStringList paths;
    paths.append(genom);
    paths.append(annotation);

    // Create path if not exists
    foreach (QString path, paths){
        QDir dir(path);
        if (!dir.exists()){
            qDebug()<<Q_FUNC_INFO<<path<<" doesn't exist. It has been created";
            if (!dir.mkpath(path)){
                qDebug()<<Q_FUNC_INFO<<"cannot create path "<<path;
                return;
            }
        }
    }

    setGenomPath(genom);
    setAnnotationPath(annotation);

}

QStringList App::avaibleGenoms() const
{
    QStringList list;
    QDir dir(genomPath());

    dir.setNameFilters(QStringList()<<"*.genome");
    foreach (QFileInfo info, dir.entryList(QDir::Files|QDir::NoDotAndDotDot))
    {
        list.append(info.fileName());
    }

    return list;
}

App::App(QObject *parent) :
    QObject(parent)
{
    mAwesome = new QtAwesome(this);
    mAwesome->initFontAwesome();
    setDefaultPath();
}

}}
