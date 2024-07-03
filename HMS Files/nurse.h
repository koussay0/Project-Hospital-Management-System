#ifndef NURSE_H
#define NURSE_H

#include <QWidget>
#include <QDialog>
#include "login.h"
#include "admin.h"
#include <QFile>
#include <QTextStream>
#include <QString>
namespace Ui {
class nurse;
}

class nurse : public QDialog
{
    Q_OBJECT

public:
    explicit nurse(QWidget *parent, QList<QList<QString>>* usersRecords_ptr, QList<QString> data);
    ~nurse();
    QList<QString> data;
    QList<QList<QString>>* usersRecords_ptr;
    QList<QString> Retrieve(QString toBeFoundID);
    void InitializeList();
    int Find(QString toBeFoundID);
    void AddPatientRecord(QString toBeAddedID);
private slots:
    void on_pushButton_clicked();

    void on_getdoctorbutton_clicked();

private:
    Ui::nurse *ui;
    QFile file;
    QList<QList<QString>> usersRecordData;
};

#endif // NURSE_H
