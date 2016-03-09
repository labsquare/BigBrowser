#include "genomsettingswidget.h"
#include "app.h"
#include <QtCore>
#include <QMessageBox>
namespace big {
namespace gui {
GenomSettingsWidget::GenomSettingsWidget(QWidget * parent)
    :AbstractSettingsWidget(parent)
{
    setWindowTitle("genom");

    mView  = new QTableView;
    mModel = new GenomModel;
    mView->setModel(mModel);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::SingleSelection);

    QPushButton * addLocalButton  = new QPushButton(App::awesome()->icon(fa::download),tr("Add from computer"));
    QPushButton * addRemoteButton = new QPushButton(App::awesome()->icon(fa::plus),tr("Add from IGV server"));
    QPushButton * removeButton    = new QPushButton(App::awesome()->icon(fa::minus),tr("Remove"));

    QVBoxLayout * buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addLocalButton);
    buttonLayout->addWidget(addRemoteButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(removeButton);

    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mView);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    loadGenomList();
    QAction * refreshAction = new QAction(tr("Refresh"),this);
    mView->addAction(refreshAction);
    mView->setContextMenuPolicy(Qt::ActionsContextMenu	);

    connect(addLocalButton,SIGNAL(clicked(bool)),this,SLOT(addLocalFile()));
    connect(addRemoteButton,SIGNAL(clicked(bool)),this,SLOT(addRemoteFile()));
    connect(removeButton,SIGNAL(clicked(bool)),this,SLOT(removeFile()));
    connect(refreshAction,SIGNAL(triggered(bool)),this,SLOT(loadGenomList()));


}

bool GenomSettingsWidget::save()
{
    return true;
}

bool GenomSettingsWidget::load()
{
    return true;
}

void GenomSettingsWidget::loadGenomList()
{
    mModel->loadList();
    mView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void GenomSettingsWidget::removeFile()
{

    if (mView->selectionModel()->selectedRows().count() == 1)
    {
        int ret = QMessageBox::warning(this,
                                       tr("Delete genom"),
                                       tr("Are you sure you want to delete this genom ?"),
                                       QMessageBox::Ok|QMessageBox::Discard
                                       );

        if (ret == QMessageBox::Ok)
        {
            int row = mView->currentIndex().row();
            mModel->removeFile(row);
        }

    }


}

void GenomSettingsWidget::addLocalFile()
{

    QString path = QFileDialog::getOpenFileName(this,
                                                tr("impport genom"),
                                                QDir::homePath(),
                                                "*.genome"
                                                );
    if (!path.isEmpty())
    {
        mModel->addFile(path);

    }




}

void GenomSettingsWidget::addRemoteFile()
{

}

}}
