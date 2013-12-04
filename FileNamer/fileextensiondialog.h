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


private slots:
    void on_buttonBox_accepted();

private:
    Ui::fileExtensionDialog *ui;

};

#endif // FILEEXTENSIONDIALOG_H
