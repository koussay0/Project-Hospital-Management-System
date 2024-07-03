#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QDialog>
#include "login.h"
#include <QFile>
#include <QTextStream>
#include <QDateTimeEdit>
namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();

private slots:
    void on_pushButton_clicked();

    void on_addappointementbutton_clicked();

    void on_resechedulebuttom_clicked();

    void on_cancelappointementbutton_clicked();

    void on_showrecord_clicked();

private:
    Ui::user *ui;
};

#endif // USER_H
