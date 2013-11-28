#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //QString x = "";
    ui->setupUi(this);
  //  connect (ui->pushButton,SIGNAL(clicked()), ui->label,SLOT(setText(QString)));
}

void MainWindow::on_pushButton_clicked()
{
    QString Path = QFileDialog::getExistingDirectory (this,
                                          tr ("Open Directory"), "/",
                                              QFileDialog::ShowDirsOnly |
                                          QFileDialog::DontResolveSymlinks);
    ui->label->setText(Path);

}

MainWindow::~MainWindow()
{
    delete ui;
}
