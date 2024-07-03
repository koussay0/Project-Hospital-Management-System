#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT
    QList<QString>* data;
    QList<QList<QString>>* recordData;

public:
    explicit Registration(QWidget *parent, QList<QString>* data, QList<QList<QString>>* recordsData);
    ~Registration();

private slots:

    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
