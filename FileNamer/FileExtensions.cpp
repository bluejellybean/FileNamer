#include "FileExtensions.h"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <QtWidgets>
#include <QTextStream>
#include <QFileDialog>
fileExtensions::fileExtensions(){

}

QString fileExtensions::getPathToFileExtensions(){

    return pathToFileExtensions;
}

void fileExtensions::loadFileExtension(){
    pathToFileExtensions = QCoreApplication::applicationDirPath();
    pathToFileExtensions.append("/fileExtensions.txt");
}


QString fileExtensions::newUserExtension(){
    QString newString = "nope";//TEMP
    //check if string is already in file
    return newString;
}
