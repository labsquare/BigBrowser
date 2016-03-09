#include "pathsettingswidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "app.h"

namespace big {
namespace gui {
PathSettingsWidget::PathSettingsWidget(QWidget * parent)
    :AbstractSettingsWidget(parent)
{

  mGenomPath      = new QLineEdit;
  mAnnotationPath = new QLineEdit;

  QAction * setPathAction = new QAction(this);
  setPathAction->setText("path");
   setPathAction->setIcon(App::awesome()->icon(fa::bell));

  mGenomPath->addAction(setPathAction,QLineEdit::TrailingPosition);

  QFormLayout * mainLayout = new QFormLayout;

  mainLayout->addRow(tr("genom path"), mGenomPath);
  mainLayout->addRow(tr("annotation path"), mAnnotationPath);


  setLayout(mainLayout);
  setWindowTitle("Data path");





}

bool PathSettingsWidget::save()
{

    return true;
}

bool PathSettingsWidget::load()
{

    return true;
}

}} // end namespace
