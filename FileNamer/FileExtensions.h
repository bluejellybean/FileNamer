#ifndef FILEEXTENSIONS_H
#define FILEEXTENSIONS_H
#include <QMainWindow>

class fileExtensions
{
public:
    fileExtensions();
    QString getPathToFileExtensions();
    QString newUserExtension();
    void loadFileExtension();

private:
    QString pathToFileExtensions;

};

#endif // FILEEXTENSIONS_H
