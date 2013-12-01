#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>



//#include <stdlib.h>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //make combo boxes
    QStringList exampleList = (QStringList() <<"0example"<<"0_example"<<"example0"<<"example_0");
    ui->comboBox->addItems(exampleList);
    //can add other file extensions here
    QStringList fileExtensionList = (QStringList() <<"All"<<"jpg"<<"txt");
    ui->comboBox_2->addItems((fileExtensionList));
}

QString MainWindow::getComboBoxIndex(QString newFileName, QString indexNumber){

    //EXAMPLE.jpgs will get changed to an real string variable with proper suffix
    switch(ui->comboBox->currentIndex()){
    case 0:
        //0example
        return (indexNumber+newFileName+".");
        break;
    case 1:
        //0_example
        return (indexNumber+"_"+newFileName+".");
        break;
    case 2:
        //example0
        return (newFileName+indexNumber+".");
        break;
    case 3:
        //example_0
        return (newFileName+"_"+indexNumber+".");
        break;
    }
}


bool MainWindow::continueMessage() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Continue?"),"<p>Are you sure you want to contiune?", QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes){
        return true;
    } else {
        return false;
    }
}

void MainWindow::on_pushButton_clicked() {
    QString newFileName = ui->lineEdit->text();
    QString path = QFileDialog::getExistingDirectory (this,
                                          tr ("Open Directory"), "/",
                                              QFileDialog::ShowDirsOnly |
                                          QFileDialog::DontResolveSymlinks);

    //Renames a hardcoded filename
    //TODO: change this to work with multiple names/file types
    QDir dir = path;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting( QDir::Reversed);

    if(continueMessage() == true){

        int counter = 0;
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            QString fileInfosName = fileInfo.fileName();
            QString fileInfosSuffix = fileInfo.suffix();

            QString indexNumber = QString::number(counter);

            QString newFileNameWithoutExtension = getComboBoxIndex(newFileName, indexNumber);

            if(fileInfosSuffix == ui->comboBox_2->currentText() || ui->comboBox_2->currentText() == "All") {
                QFile::rename(path+"/"+fileInfosName, path + "/" + newFileNameWithoutExtension + fileInfosSuffix);
                counter += 1;
            }
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
