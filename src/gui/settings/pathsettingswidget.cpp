#include "pathsettingswidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "app.h"

namespace big {
namespace gui {
PathSettingsWidget::PathSettingsWidget(QWidget * parent)
    :AbstractSettingsWidget(parent)
{

    mGenomPath      = new QLineEdit;
    mAnnotationPath = new QLineEdit;

    QGroupBox * mBox = new QGroupBox(this);

    QAction * genomPathAction      = new QAction(App::awesome()->icon(fa::file),"",mGenomPath);
    QAction * annotationPathAction = new QAction(App::awesome()->icon(fa::file),"",mAnnotationPath);

    mGenomPath->addAction(genomPathAction,QLineEdit::TrailingPosition);
    mAnnotationPath->addAction(annotationPathAction,QLineEdit::TrailingPosition);

    QFormLayout * mainLayout = new QFormLayout;

    mainLayout->addRow(tr("genom path"), mGenomPath);
    mainLayout->addRow(tr("annotation path"), mAnnotationPath);

    mBox->setLayout(mainLayout);
    mBox->setTitle(tr("Data folder path"));
    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mBox);

    setLayout(vLayout);
    setWindowTitle("Data path");


    connect(genomPathAction,&QAction::triggered, this, &PathSettingsWidget::openFileBrowser);
    connect(annotationPathAction,&QAction::triggered, this, &PathSettingsWidget::openFileBrowser);

}

bool PathSettingsWidget::save()
{
    QSettings settings;
    settings.beginGroup("data");
    settings.setValue("genomPath", mGenomPath->text());
    settings.setValue("annotationPath", mAnnotationPath->text());
    settings.endGroup();
    return true;
}

bool PathSettingsWidget::load()
{
    QSettings settings;
    settings.beginGroup("data");
    mGenomPath->setText(settings.value("genomPath").toString());
    mAnnotationPath->setText(settings.value("annotationPath").toString());
    settings.endGroup();

    return true;
}

void PathSettingsWidget::openFileBrowser()
{

    QFileDialog dialog(this);
    QString path = dialog.getExistingDirectory(this);

    if (path.isEmpty())
        return;

    if (sender()->parent() == mGenomPath)
        mGenomPath->setText(path);

    if (sender()->parent() == mAnnotationPath)
        mAnnotationPath->setText(path);


}

}} // end namespace
