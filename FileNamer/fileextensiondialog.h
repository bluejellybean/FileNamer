#ifndef FILEEXTENSIONDIALOG_H
#define FILEEXTENSIONDIALOG_H

#include <QDialog>

namespace Ui {
class fileExtensionDialog;
}

class fileExtensionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fileExtensionDialog(QWidget *parent = 0);
    ~fileExtensionDialog();

    QString getLineContents();
    bool isAcceptedValue;
    void isAccepted(bool);

   // QString getPathToFileExtensions();
   // QString fileExtensions::getPathToFileExtensions(){
   //    return pathToFileExtensions;
   //}



   // QString newUserExtension();
   // void loadFileExtension();


private slots:
    void on_buttonBox_accepted();

private:
    Ui::fileExtensionDialog *ui;

    //    QString pathToFileExtensions;
    //    QString setText();

};

#endif // FILEEXTENSIONDIALOG_H
