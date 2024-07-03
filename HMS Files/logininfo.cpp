#include "logininfo.h"
#include "ui_logininfo.h"
#include "login.h"
#include "registration.h"
#include "admin.h"
#include "nurse.h"
#include "doctor.h"
#include "user.h"

#include <QTimer>

loginInfo::loginInfo(QWidget *parent, QList<QString>* data, QList<QList<QString>>* recordsData)
    : QDialog(parent)
    , ui(new Ui::loginInfo)
{
    ui->setupUi(this);
    this->data_ptr = data;
    this->recordData = recordsData;

    ui->background->lower(); //Decreases zIndex of this UI element

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}


loginInfo::~loginInfo()
{
    delete ui;
}

void loginInfo::on_pushButton_clicked()
{
    QString hisUsername = this->ui->textEdit->toPlainText();
    QString hisPassword = this->ui->textEdit_2->toPlainText();

    hisUsername = hisUsername.trimmed(); // Trims any spaces at the end
    hisPassword = hisPassword.trimmed(); // Trims any spaces at the end
    index = -1;

    QList<QString> data = *data_ptr;
    for (int i = 0; i < data.count(); i++)
    {
        QString username, password;
        QTextStream input(&data[i]);
        input >> username >> password;
        if (hisUsername == username && hisPassword == password)
        {
            index = i;
            qDebug() << "found";
        }
    }

    if (index == -1)
    {
        this->ui->pushButton->setText("Invalid Details");
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        this->ui->pushButton->setText("Login");
        return;
    }

    QTextStream input(&data[index]);

    QString ownID, role;
    input >> role >> role >> role >> ownID; // First 2 to ignore name and password;

    QWidget* parent = static_cast<QWidget*>(this->parent());

    //The username variable is hisUsername;
    //Deals with role accordingly

    if (role == "admin")
    {
        admin* adminWindow = new admin(parent, data_ptr, recordData);
        adminWindow->show();
        delete this;
    }
    else  if (role == "patient")
    {
        user* userWindow = new user(parent);
        userWindow->show();
        delete this;
    }
    else if (role == "doctor")
    {
        doctor* doctorWindow = new doctor(parent, data, recordData, ownID);
        doctorWindow->show();
        delete this;
    }
    else if (role == "nurse")
    {
        nurse* nurseWindow = new nurse(parent, recordData, data);
        nurseWindow->show();
        delete this;
    }
}


void loginInfo::on_pushButton_2_clicked()
{
    static_cast<logIn*>(parent())->show();
    delete(this);
}

