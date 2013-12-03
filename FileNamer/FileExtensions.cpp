#include "FileExtensions.h"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <QtWidgets>
#include <QTextStream>
#include <QFileDialog>
fileExtensions::fileExtensions(){
    qDebug() << "construct";
}

QString fileExtensions::getPathToFileExtensions(){

    return pathToFileExtensions;
}

void fileExtensions::loadFileExtension(){
    pathToFileExtensions = QCoreApplication::applicationDirPath();
    pathToFileExtensions.append("/fileExtensions.txt");
}
