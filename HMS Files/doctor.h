#ifndef DOCTOR_H
#define DOCTOR_H

#include <QWidget>
#include <QDialog>
#include <QHash>
#include "login.h"

namespace Ui {
class doctor;
}

class doctor : public QDialog
{
    Q_OBJECT

    QString ownID;
    QList<QString> data;
    QList<QList<QString>>* usersRecords_ptr;
public:
    explicit doctor(QWidget *parent, QList<QString> data, QList<QList<QString>>* usersRecords, QString ownID);
    ~doctor();

private slots:
    void on_pushButton_clicked();

    void on_EditPatientRecord_clicked();

    void on_CancelAppointment_clicked();

    void on_AddAppointment_clicked();

private:
    Ui::doctor *ui;
    int Find(QString id);
    QList<QString> Retrieve(QString id);


    void InitializeList();
    void AddPatientRecord(QString id);

};

#endif // DOCTOR_H
