#include "login.h"
#include "ui_login.h"
#include "logininfo.h"
#include "registration.h"
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "admin.h"


logIn::logIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::logIn)
{
    ui->setupUi(this);
    QPixmap b(":/Images/Login2.png");
    b = b.scaled(ui->BackgroundLabel->size());
    ui->BackgroundLabel->setPixmap(b);
    loginInfoPath = "C:\\Users\\kouss\\Desktop\\Hospital Management System\\HMS_CSLab\\HMS\\Data\\loginData.txt";
    userRecordsPath = "C:\\Users\\kouss\\Desktop\\Hospital Management System\\HMS_CSLab\\HMS\\Data\\usersData.txt";

    ExtractData();
}

void logIn::ExtractData()
{
    QFile file(loginInfoPath);

    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "Failed to open file" << "\n";
        return;
    }


    QTextStream stream(&file);

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        data.push_back(line);
    }

    file.close();

    QFile recordsFile(userRecordsPath);

    if (!recordsFile.open(QFile::ReadOnly))
    {
        qDebug() << "Failed to open file" << "\n";
        return;
    }

    QTextStream recordsStream(&recordsFile);

    while (!recordsStream.atEnd())
    {
        QString userInfo = recordsStream.readLine();
        int recordsNumber;
        recordsStream >> recordsNumber;
        recordsStream.readLine();
        QList<QString> userInfoAndRecords;
        userInfoAndRecords.push_back(userInfo);
        userInfoAndRecords.push_back(QString::number(recordsNumber));
        for (int i = 0; i < recordsNumber; i++)
        {
            QString record = recordsStream.readLine();
            userInfoAndRecords.push_back(record);
        }
        usersRecords.push_back(userInfoAndRecords);
    }
    recordsFile.close();
}

logIn::~logIn()
{
    QFile file(loginInfoPath);

    file.open(QFile::WriteOnly);

    QTextStream stream(&file);
    for (int i = 0; i < data.count(); i++)
    {
        stream << data[i] << "\n";
    }
    file.close();

    QFile recordsFile(userRecordsPath);

    if (!recordsFile.open(QFile::WriteOnly))
    {
        qDebug() << "Failed to open file" << "\n";
        return;
    }

    QTextStream recordsStream(&recordsFile);

    for (int i = 0; i < usersRecords.count(); i++)
    {
        for (int j = 0; j < usersRecords[i].count(); j++)
        {
            recordsStream << usersRecords[i][j] << "\n";
        }
    }

    recordsFile.close();
    delete ui;
}

void logIn::on_LoginButton_clicked()
{
    this->hide();
    loginInfo* login = new loginInfo(this, &data, &usersRecords);
    login->show();
}


void logIn::on_SignUpButton_clicked()
{
    this->hide();
    Registration* registration = new Registration(this, &data, &usersRecords);
    registration->show();
}
