#include "nurse.h"
#include "ui_nurse.h"

nurse::nurse(QWidget *parent, QList<QList<QString>>* usersRecords_ptr, QList<QString> data)
    : QDialog(parent)
    , ui(new Ui::nurse)
{
    ui->setupUi(this);
    QPixmap b1(":/Images/nurse.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);
    this->usersRecords_ptr = usersRecords_ptr;
    this->data = data;
    InitializeList();
}

nurse::~nurse()
{
    delete ui;
}

void nurse::InitializeList()
{
    ui->assignedpatients->setColumnCount(3);
    ui->assignedpatients->setColumnWidth(0, 150);
    ui->assignedpatients->setColumnWidth(1, 50);
    ui->assignedpatients->setColumnWidth(2, 300);
    QStringList headerLabels;
    headerLabels << "Name" << "ID" << "Diagnosis and Treatment";
    ui->assignedpatients->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->assignedpatients->setHorizontalHeaderLabels(headerLabels);


    for (int i = 0; i < data.count(); i++)
    {
        QTextStream input(&data[i]);
        QString name, role, id;

        input >> name >> role >> role >> id;

        if (role != "patient") continue;

        AddPatientRecord(id);
    }

    //qDebug() << ownID;

}

QList<QString> nurse::Retrieve(QString toBeFoundID)
{
    QList<QList<QString>> usersRecords = *usersRecords_ptr;
    for (int i = 0; i < usersRecords.count(); i++)
    {
        QString userInfo = usersRecords[i][0];
        QTextStream input(&userInfo);
        QString id;
        input >> id >> id;

        if (id == toBeFoundID)
        {
            return (usersRecords[i]);
        }
    }
}

int nurse::Find(QString toBeFoundID)
{
    QList<QList<QString>> usersRecords = *usersRecords_ptr;
    for (int i = 0; i < usersRecords.count(); i++)
    {
        QString userInfo = usersRecords[i][0];
        QTextStream input(&userInfo);
        QString id;
        input >> id >> id;

        if (id == toBeFoundID)
        {
            return i;
        }
    }
}


void nurse::AddPatientRecord(QString toBeAddedID)
{
    QList<QString> userRecords = Retrieve(toBeAddedID);
    QTextStream userInfo (&userRecords[0]);
    QString diagnosis = userRecords[2];

    QString name, id;

    userInfo >> name >> id;

    int index = ui->assignedpatients->rowCount();
    ui->assignedpatients->insertRow(index);
    ui->assignedpatients->setItem(index,0,new QTableWidgetItem(name));
    ui->assignedpatients->setItem(index,1,new QTableWidgetItem(id));
    ui->assignedpatients->setItem(index,2,new QTableWidgetItem(diagnosis));
    return;
}
void nurse::on_pushButton_clicked()
{
    static_cast<logIn*>(parent())->show();
    delete this;

}


void nurse::on_getdoctorbutton_clicked()
{
    QFile file("C:\\Users\\kouss\\Desktop\\Hospital Management System\\HMS_CSLab\\HMS\\Data\\nursesData.txt");
    QString nursename = this->ui->nursename->text().trimmed(); // Trimmed to remove any leading/trailing spaces

    // Convert nurse's name to QByteArray
    QByteArray ba = nursename.toUtf8(); // Convert QString to QByteArray

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QByteArray line = file.readLine().trimmed(); // Trimmed to remove any leading/trailing spaces


            if (line.contains(ba)) {
                ui->doctoroutput->setText(QString("The Nurse and the Assigned Doctor : ")+ QString(line));
                qDebug() << "read output - " << line;
                break; // If you only want to display the first match, you can break here
            }
        }
        file.close();
    } else {
        qDebug() << "Failed to open file";
    }



}

