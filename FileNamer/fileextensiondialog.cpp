#include "fileextensiondialog.h"
#include "ui_fileextensiondialog.h"

fileExtensionDialog::fileExtensionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileExtensionDialog)
{
    ui->setupUi(this);
}

fileExtensionDialog::~fileExtensionDialog()
{
    delete ui;
}
QString fileExtensionDialog::getLineContents(){
        return ui->lineEdit->text();
}


void fileExtensionDialog::isAccepted(bool mybool){
    if(mybool == true && !ui->lineEdit->text().trimmed().isEmpty()){
        isAcceptedValue = true;
    } else {
        isAcceptedValue = false;
    }
}

void fileExtensionDialog::on_buttonBox_accepted(){
    isAccepted(true);
}
