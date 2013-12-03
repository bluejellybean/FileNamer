#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileextensiondialog.h"
#include <iostream>
#include <QFileDialog>

#include <QDebug>
#include <QTextStream>




//#include <stdlib.h>
#include <QtWidgets>



//fileExtensions fileExten;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //make combo boxes
    QStringList nameFormatList = (QStringList() <<"example 0"<<"0example"<<"0_example"<<"example0"<<"example_0");
    ui->nameFormatBox->addItems(nameFormatList);


    //can add other file extensions here
    QStringList fileExtensionList;
    pathToFileExtensions = QCoreApplication::applicationDirPath();
    pathToFileExtensions.append("/fileExtensions.txt");

    fileExtensionList += readQStringLists(pathToFileExtensions);

    ui->fileExtensionBox->addItems((fileExtensionList));
}


QStringList MainWindow::readQStringLists(QString Filename){
    QFile mFile(Filename);
    QStringList QStringListFromFile;
    if(!mFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file";
        return QStringListFromFile;
    }

    QTextStream in(&mFile);
    while (!in.atEnd()){
        QString mText = in.readLine();
        QStringListFromFile += mText;
    }

    mFile.close();
    return QStringListFromFile;
}

void MainWindow::writeStringToFile(QString Filename, QString newString){
    QFile mFile(Filename);

    if(!mFile.open(QFile::Append | QFile::Text)) {
        qDebug()<< "could not open file to write";
        return;
    }

   QTextStream out(&mFile);
   //otherwise it works kinda okay right now..still need to make the actual checks work
  //  out <<"\n" ;
    out<< newString;
    out.flush();
    mFile.flush();
}



//TODO: allow users to add/remove their own + save
QString MainWindow::getnameFormatBoxIndex(QString newFileName, QString indexNumber){ 


    //EXAMPLE.jpgs will get changed to an real string variable with proper suffix
    switch(ui->nameFormatBox->currentIndex()){
        //example 0
    case 0:
        return (newFileName+" "+indexNumber+".");
        break;
    case 1:
        //0example
        return (indexNumber+newFileName+".");
        break;
    case 2:
        //0_example
        return (indexNumber+"_"+newFileName+".");
        break;
    case 3:
        //example0
        return (newFileName+indexNumber+".");
        break;
    case 4:
        //example_0test
        return (newFileName+"_"+indexNumber+".");
        break;
    }
}


bool MainWindow::continueMessage(QString path) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Continue?"),"<p>Are you sure you want to contiune?<p>" + path, QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes){
        return true;
    } else {
        return false;
    }
}

void MainWindow::on_pushButton_clicked() {
    QString newFileName = ui->lineEdit->text();
    QString path = QFileDialog::getExistingDirectory (this, tr ("Open Directory"), "/",
                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //TODO: when clicking cancel you still have to check yes or no

    //Renames a hardcoded filename
    //TODO: change this to work with multiple names/file types
    QDir dir = path;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting( QDir::Reversed);

    if(continueMessage(path) == true){

        int counter = 0;
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            QString fileInfosName = fileInfo.fileName();
            QString fileInfosSuffix = fileInfo.suffix();

            QString indexNumber = QString::number(counter);

            QString newFileNameWithoutExtension = getnameFormatBoxIndex(newFileName, indexNumber);

            if(fileInfosSuffix == ui->fileExtensionBox->currentText() || ui->fileExtensionBox->currentText() == "All") {
                 QFile::rename(path+"/"+fileInfosName, path+"/"+newFileNameWithoutExtension + fileInfosSuffix);
                 counter += 1;
            }
        }
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_File_Extension_triggered()
{
    bool MARKER = true;
    fileExtensionDialog newDialog;
    newDialog.setModal(true);
    newDialog.exec();
    if(newDialog.isAcceptedValue == true){
        QString newString = newDialog.getLineContents();
        for(int i = 0; i < ui->fileExtensionBox->count(); i++){
            ui->fileExtensionBox->setCurrentIndex(i);//IM SORRY
            if(ui->fileExtensionBox->currentText() == newString){
                MARKER = false;
            }
        }
        if(MARKER){
            writeStringToFile(pathToFileExtensions, "\n"+newString);
            ui->fileExtensionBox->addItem(newString);
        }
    }
}

void MainWindow::on_actionDelete_Current_Extension_triggered(){

    ui->fileExtensionBox->removeItem(ui->fileExtensionBox->currentIndex());

    QFile mFile(pathToFileExtensions);

    if(!mFile.open(QFile::WriteOnly| QFile::Text)) {
        qDebug()<< "could not open file to write";
        return;
    }

   QTextStream out(&mFile);

   for(int i = 0; i < ui->fileExtensionBox->count(); i++){
       ui->fileExtensionBox->setCurrentIndex(i);

       out << ui->fileExtensionBox->currentText();
       out<<"\n";
   }



    out.flush();
    mFile.flush();
    mFile.close();

}




