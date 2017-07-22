#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <string>
#include <fstream>
#include <vector>
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")
using namespace std;

bool isMailChar(char x);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filename = "page.html";
    file.open(filename.c_str(), ios::out);
    file << "Nothing" << endl;
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_extractButton_clicked()
{
    ui->textBrowser->setText("");
    qURL = ui->textEdit->toPlainText();
    sURL = qURL.toStdString();


    if (!URLDownloadToFileA(NULL, sURL.c_str(), filename.c_str(), 0, NULL) == S_OK)
    {
        ui->errorLabel->setText("Unable to download the file");
        return;
    }

    file.open(filename.c_str(), ios::in);

    if (!file.good())
    {
        ui->errorLabel->setText("Unable to open the file");
        file.close();
        return;
    }

    string part, page;
    while (!file.eof())
    {
        getline(file, part);
        page += part;
        page += "\n";
    }
    file.close();

    vector<string> mails;
    string mail;

    for (int i = 0; i < page.size(); i++)
        {
            if (page.at(i) == '@')
            {
                while (isMailChar(page.at(i)))
                {
                    if (i - 1 > 0)
                    {
                        i--;
                    }
                }
                mail = "";
                while (isMailChar(page.at(i+1)))
                {
                    if (i + 1 < page.size())
                    {
                        i++;
                        mail += page.at(i);
                    }
                }
                mails.push_back(mail);
            }
        }

    for (int i = 0; i<mails.size(); i++)
    {
        QString s = QString::fromStdString(mails.at(i));
        ui->textBrowser->append(s);

    }


}

void MainWindow::on_textEdit_textChanged()
{
    ui->errorLabel->setText("");
}


bool isMailChar(char x)
{
    if (x == 46)
    {
        return true;
    }
    if (x >= 48 && x <= 57)
    {
        return true;
    }
    if (x >= 65 && x <= 90)
    {
        return true;
    }
    if (x == 95)
    {
        return true;
    }
    if (x >= 97 && x <= 122)
    {
        return true;
    }
    if (x == '@')
    {
        return true;
    }
    return false;
}
