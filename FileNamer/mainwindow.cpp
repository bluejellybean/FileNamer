#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>

//#include <stdlib.h>
//#include <QtWidgets>

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
    QString path = QFileDialog::getExistingDirectory (this,
                                          tr ("Open Directory"), "/",
                                              QFileDialog::ShowDirsOnly |
                                          QFileDialog::DontResolveSymlinks);
  //  ui->label->setText(path);
    //Renames a hardcoded filename
    //TODO: change this to work with multiple names/file types
    QDir dir = path;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting( QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

        QString fileInfosName = fileInfo.fileName();
        ui->label->setText(fileInfosName);

        QString qStr = QString::number(i);

        QFile::rename(path+"/"+fileInfosName, path+"/"+qStr+"newOne.jpg");

    }



}

MainWindow::~MainWindow()
{
    delete ui;
}
