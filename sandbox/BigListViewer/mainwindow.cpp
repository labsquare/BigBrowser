#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "biglistmodel.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    BigListModel * model = new BigListModel("/home/bioinfo/Dev/BigListViewer/data.txt");

   ui->listView->setModel(model);
   model->load();

}

MainWindow::~MainWindow()
{
    delete ui;
}
