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
    ui->setupUi(this);

    QStringList list=(QStringList()<<"0example"<<"0_example"<<"example0"<<"example_0");
    ui->comboBox->addItems(list);
}

QString MainWindow::getComboBoxIndex(QString newFileName, QString indexNumber){

    //EXAMPLE.jpgs will get changed to an real string variable with proper suffix
    switch(ui->comboBox->currentIndex()){
    case 0:
        //0example
        return (indexNumber+newFileName+".jpg");
        break;
    case 1:
        //0_example
        return (indexNumber+"_"+newFileName+".jpg");
        break;
    case 2:
        //example0
        return (newFileName+indexNumber+".jpg");
        break;
    case 3:
        //example_0
        return (newFileName+"_"+indexNumber+".jpg");
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString newFileName = ui->lineEdit->text();
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

        QString indexNumber = QString::number(i);

//path+"/"+qStr+"newOne.jpg"
        QFile::rename(path+"/"+fileInfosName, path + "/" + getComboBoxIndex(newFileName,indexNumber) );

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
