#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileextensiondialog.h"
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QtWidgets>
#include <QDebug>


//fileExtensions fileExten;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //make combo boxes
    QStringList nameFormatList = (QStringList() <<"example 0"<<"0example"<<"0_example"<<"example0"<<"example_0");
    ui->nameFormatBox->addItems(nameFormatList);

    //creates path to the file extensions
    pathToFileExtensions = QCoreApplication::applicationDirPath();
    pathToFileExtensions.append("/fileExtensions.txt");
    //Fills combo Box with file extensions
    ui->fileExtensionBox->addItems((readQStringLists(pathToFileExtensions)));
}

//returns QStringList for adding to combo boxes
QStringList MainWindow::readQStringLists(QString Filename){
    QFile mFile(Filename);
    QStringList QStringListFromFile;
    if(!mFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file!";
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

//Adds a new string to a file
void MainWindow::writeStringToFile(QString Filename, QString newString){
    QFile mFile(Filename);

    if(!mFile.open(QFile::Append | QFile::Text)) {
        qDebug()<< "could not open file to write";
        return;
    }

   QTextStream out(&mFile);
    out<< newString;
    out.flush();
    mFile.flush();
}

//
QString MainWindow::getNameFormatBoxIndex(QString newFileName, QString indexNumber){


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

//prompts user if they want to continue with name changes and shows them the dir they set
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
    if(path != ""){
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

                QString newFileNameWithoutExtension = getNameFormatBoxIndex(newFileName, indexNumber);

                if(fileInfosSuffix == ui->fileExtensionBox->currentText() || ui->fileExtensionBox->currentText() == "All") {
                     QFile::rename(path+"/"+fileInfosName, path+"/"+newFileNameWithoutExtension + fileInfosSuffix);
                     counter += 1;
                }
            }
        }
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
//Opens dialog and lets user enter new file extension
void MainWindow::on_actionNew_File_Extension_triggered(){

    fileExtensionDialog newDialog;
    newDialog.setModal(true);
    newDialog.exec();

    bool noDuplicates = true;
    if(newDialog.isAcceptedValue == true){
        QString newString = newDialog.getLineContents();
        noDuplicates = checkBoxForDuplicates(newString);

        if(noDuplicates){
            writeStringToFile(pathToFileExtensions, "\n"+newString);
            ui->fileExtensionBox->addItem(newString);
        }
    }
}

//checks if there is already a file extension of the same value
bool MainWindow::checkBoxForDuplicates(QString newString){

    for(int i = 0; i < ui->fileExtensionBox->count(); i++){
        ui->fileExtensionBox->setCurrentIndex(i);
        if(ui->fileExtensionBox->currentText() == newString){
            return false;
        }
    }
    return true;
}

//deletes extension that user is currently on(in the comboBox)
void MainWindow::on_actionDelete_Current_Extension_triggered(){

    //removes item from comboBox
    ui->fileExtensionBox->removeItem(ui->fileExtensionBox->currentIndex());

    QFile mFile(pathToFileExtensions);
    if(!mFile.open(QFile::WriteOnly| QFile::Text)) {
        qDebug()<< "could not open file to write";
        return;
    }

   QTextStream out(&mFile);

   //loops through fileExtension box and prints each item to a newline in file
   for(int i = 0; i < ui->fileExtensionBox->count(); i++){
       ui->fileExtensionBox->setCurrentIndex(i);
       out << ui->fileExtensionBox->currentText();

       //prints newline except at the end
       if(i != ui->fileExtensionBox->count() - 1){
           out<<"\n";
       }
   }
    out.flush();
    mFile.flush();
    mFile.close();
}




