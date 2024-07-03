#include "admin.h"
#include "ui_admin.h"
#include <QTimer>
#include <QStandardItemModel>

admin::admin(QWidget *parent, QList<QString>* Data, QList<QList<QString>>* recordData)
    : QDialog(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);

    QPixmap b1(":/Images/admin.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);
    index = 0;
    this->data_ptr = Data;
    this->usersRecords_ptr = recordData;

    QStringList headerLabels;
    headerLabels << "Name" << "ID" << "Role";
    ui->usersList->setColumnCount(3);
    ui->usersList->setHorizontalHeaderLabels(headerLabels);


    InitializeList();
}

admin::~admin()
{
    delete ui;
}

void admin::on_pushButton_clicked()
{
    static_cast<logIn*>(parent())->show();
    delete this;
}

void admin::on_DeleteRecordButton_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->PatientDetailsTable->model());
    QString id = ui->PatientIDToBeDeleted->toPlainText();
    for (int i = 0; i < ui->PatientDetailsTable->rowCount(); i++)
    {
        QModelIndex index = model->index(i,1);
        QVariant data = model->data(index, Qt::DisplayRole);

        if (id.trimmed() == data.toString().trimmed())
        {
            model->removeRow(i);
            break;
        }
    }

    int index = Find(id);
    usersRecords_ptr->remove(index);

    for (int i = 0; i < data_ptr->count(); i++)
    {
        QTextStream input(&(*data_ptr)[i]);

        QString thisID;

        input >> thisID >> thisID >> thisID >> thisID;

        if (id.trimmed() == thisID)
        {
            data_ptr->remove(i);
            return;
        }
    }
    this->ui->DeleteRecordButton->setText("Invalid Details");
    QEventLoop loop;
    QTimer::singleShot(1000, &loop, &QEventLoop::quit);
    loop.exec();
    this->ui->DeleteRecordButton->setText("Delete Record");
}

void admin::InitializeList()
{
    QList<QString> data = *data_ptr;
    for (int i = 0; i < data.count(); i++)
    {
        QTextStream input(&data[i]);
        QString name, id, role;
        input >> name >> role >> role >> id;
        qDebug() << role;
        if (role == "admin") continue;
        int rowIndex = ui->usersList->rowCount();
        ui->usersList->insertRow(rowIndex);
        ui->usersList->setItem(rowIndex,0,new QTableWidgetItem(name));
        ui->usersList->setItem(rowIndex,1,new QTableWidgetItem(id));
        ui->usersList->setItem(rowIndex,2,new QTableWidgetItem(role));
    }

    ui->PatientDetailsTable->setColumnCount(3);
    ui->PatientDetailsTable->setColumnWidth(0, 150);
    ui->PatientDetailsTable->setColumnWidth(1, 50);
    ui->PatientDetailsTable->setColumnWidth(2, 300);
    QStringList headerLabels;
    headerLabels << "Name" << "ID" << "Diagnosis and Treatment";
    ui->PatientDetailsTable->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->PatientDetailsTable->setHorizontalHeaderLabels(headerLabels);

    for (int i = 0; i < data.count(); i++)
    {
        QTextStream input(&data[i]);
        QString name, role, id;

        input >> name >> role >> role >> id;

        if (role != "patient") continue;

        AddPatientRecord(id);
    }
}

QList<QString> admin::Retrieve(QString toBeFoundID)
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

int admin::Find(QString toBeFoundID)
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


void admin::AddPatientRecord(QString toBeAddedID)
{
    QList<QString> userRecords = Retrieve(toBeAddedID);
    QTextStream userInfo (&userRecords[0]);
    QString diagnosis = userRecords[2];

    QString name, id;

    userInfo >> name >> id;

    int index = ui->PatientDetailsTable->rowCount();
    ui->PatientDetailsTable->insertRow(index);
    ui->PatientDetailsTable->setItem(index,0,new QTableWidgetItem(name));
    ui->PatientDetailsTable->setItem(index,1,new QTableWidgetItem(id));
    ui->PatientDetailsTable->setItem(index,2,new QTableWidgetItem(diagnosis));
    return;
}

void admin::on_pushButton_2_clicked(){

};
void admin::on_Assign_clicked()
{
    QString doctorname = this->ui->DoctorName->text();
    QString nursename = this->ui->NurseName->text();
    //nurses.push_back(std::make_pair(doctorname,nursename));
     QFile file("C:\\Users\\kouss\\Desktop\\Hospital Management System\\HMS_CSLab\\HMS\\Data\\nursesData.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Append))
    {
         QTextStream stream(&file);
        stream << doctorname << " "<<nursename<<"\n";
        qDebug()<<"Write done";

    }

}

