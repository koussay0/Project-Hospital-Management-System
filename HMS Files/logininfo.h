#ifndef LOGININFO_H
#define LOGININFO_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QList>

namespace Ui {
class loginInfo;
}

class loginInfo : public QDialog
{
    Q_OBJECT

    QList<QString>* data_ptr;
    QList<QList<QString>>* recordData;
    int index;

public:

    explicit loginInfo(QWidget *parent, QList<QString>* data, QList<QList<QString>>* recordData);
    ~loginInfo();

private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::loginInfo *ui;
};

#endif // LOGININFO_H
