#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setExistingDirectory();

private slots:
    void on_pushButton_clicked();

    void on_actionNew_File_Extension_triggered();

private:
    //this?
    QString pathToFileExtensions;
    void loadFileExtension();


    bool continueMessage(QString);
    //this
    QStringList readQStringLists(QString);
    void  writeStringToFile(QString, QString);
    QString getnameFormatBoxIndex(QString, QString);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
