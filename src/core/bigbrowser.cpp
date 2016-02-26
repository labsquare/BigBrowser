#include "bigbrowser.h"


BigBrowser* BigBrowser::mInstance = nullptr;

BigBrowser *BigBrowser::i()
{
    if (!mInstance)
        mInstance = new BigBrowser();

    return mInstance;

}

QString BigBrowser::databasePath()
{
    return "/tmp";
}

BigBrowser::BigBrowser(QObject *parent) : QObject(parent)
{

}
