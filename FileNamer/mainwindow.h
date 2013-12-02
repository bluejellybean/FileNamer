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

private:
    bool continueMessage(QString);
    //this
    QStringList readQStringLists(QString);

    QString getnameFormatBoxIndex(QString, QString);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
