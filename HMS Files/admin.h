#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QList>
#include <QPixmap>
#include "login.h"
#include <QPair>
#include <QFile>
#include <QTextStream>

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

    QList<QString>* data_ptr;
    QList<QList<QString>>* usersRecords_ptr;

public:
    explicit admin(QWidget *parent, QList<QString>* data, QList<QList<QString>>* recordData);
    ~admin();
    //std::vector<QPair<QString,QString>> nurses;

private slots:
    void on_pushButton_clicked();

    void on_DeleteRecordButton_clicked();

    void on_pushButton_2_clicked();

    void on_Assign_clicked();

private:
    void InitializeList();
    void AddPatientRecord(QString id);
    int Find(QString id);
    QList<QString> Retrieve(QString id);
    int index;

    Ui::admin *ui;
};

#endif // ADMIN_H
