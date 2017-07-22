#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <fstream>
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
    QString qURL;
    std::string sURL, filename;
    std::fstream file;

private slots:
    void on_extractButton_clicked();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
