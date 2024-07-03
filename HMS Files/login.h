#ifndef LOGIN_H
#define LOGIN_H


#include <QString>
#include <QList>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class logIn;
}
QT_END_NAMESPACE

class logIn : public QMainWindow
{
    Q_OBJECT

    QList<QString> data;
    QList<QList<QString>> usersRecords;
    QString loginInfoPath;
    QString userRecordsPath;

    /* IMPORTANT FOR userRecords:
     * FIRST ROW in it is the userInfo, namely userName and ID in that order;
     * SECOND ROW is number of records;
     * FIRST RECORD for PATIENT is always their Diagnosis.
     * SECOND RECORD AND AFTER for PATIENT is their appointments.
     * FIRST RECORD AND AFTER for DOCTOR is their appoitnments.
     * FIRST RECORD AND AFTER for NURSE is their assigned patients.
    */
public:

    logIn(QWidget *parent = nullptr);
    ~logIn();

    void ExtractData();

private slots:

    void on_LoginButton_clicked();

    void on_SignUpButton_clicked();

private:
    Ui::logIn *ui;
};
#endif // LOGIN_H
