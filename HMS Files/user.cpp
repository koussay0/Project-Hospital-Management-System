#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::user)
{
    ui->setupUi(this);

    QPixmap b1(":/Images/user.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);

}

user::~user()
{

    delete ui;
}

void user::on_pushButton_clicked()
{
    static_cast<logIn*>(parent())->show();
    delete this;
}


void user::on_addappointementbutton_clicked()
{
    QDate date= ui->dateTimeEdit->date();
    QString dateString = date.toString();
    QString patientname = ui->patientname->text();

}


void user::on_resechedulebuttom_clicked()
{
    QDate date= ui->dateTimeEdit->date();
    QString dateString = date.toString();
    QString patientname = ui->patientname2->text();

}


void user::on_cancelappointementbutton_clicked()
{
     QString patientname = ui->patientname3->text();

}


void user::on_showrecord_clicked()
{
    QString patientname = ui->patientname4->text();

}

