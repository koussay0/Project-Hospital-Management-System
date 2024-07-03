#include "doctor.h"
#include "ui_doctor.h"
#include <QTimer>
#include <QStandardItem>

doctor::doctor(QWidget *parent, QList<QString> data, QList<QList<QString>>* usersRecords, QString ownID)
    : QDialog(parent)
    , ui(new Ui::doctor)
{
    this->data = data;
    this->usersRecords_ptr = usersRecords;
    this->ownID = ownID;

    ui->setupUi(this);
    QPixmap b1(":/Images/doctor.jpg");
    b1 = b1.scaled(ui->bglabel->size());
    ui->bglabel->setPixmap(b1);

    InitializeList();
}

doctor::~doctor()
{
    static_cast<logIn*>(parent())->show();
    delete ui;
}

void doctor::InitializeList()
{
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

        ui->PatientList->addItem(name + " " + id);
        AddPatientRecord(id);
    }

    qDebug() << ownID;

    int index = Find(ownID);

    int recordNumber = (*usersRecords_ptr)[index].value(1).toInt();

    for (int i = 0; i < recordNumber; i++)
    {
        int recordIndex = i + 2;
        QString record = (*usersRecords_ptr)[index].value(recordIndex);
        ui->AppointmentsList->addItem(record);
    }
}




void doctor::on_pushButton_clicked()
{
    delete this;
}

QList<QString> doctor::Retrieve(QString toBeFoundID)
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

int doctor::Find(QString toBeFoundID)
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


void doctor::AddPatientRecord(QString toBeAddedID)
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

void doctor::on_EditPatientRecord_clicked()
{

    for(int i=0;i<data.count();i++)
    {
        QTextStream input(&data[i]);

        QString id, username;
        input >> username >> id >> id >> id;
        if(id == ui->PatientID_lineedit->text())
        {
            QString diagnosis = ui->Diagnosis_lineedit->text();
            qDebug() << diagnosis;
            int index = Find(id);
            (*usersRecords_ptr)[index][2] = diagnosis;

            QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->PatientDetailsTable->model());
            for (int rowIndex = 0; rowIndex < ui->PatientDetailsTable->rowCount(); rowIndex++)
            {
                QModelIndex index = model->index(rowIndex,1);
                QVariant data = model->data(index, Qt::DisplayRole);

                if (id.trimmed() == data.toString().trimmed())
                {
                    ui->PatientDetailsTable->setItem(rowIndex,2, new QTableWidgetItem(diagnosis));
                    return;
                }
            }
            return;
        }
    }
}

void doctor::on_CancelAppointment_clicked()
{
    int AppointmentIndex = ui->AppointmentNumber->toPlainText().toInt();
    if (AppointmentIndex > ui->AppointmentsList->count())
    {
        this->ui->CancelAppointment->setText("No such appointment exist");
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        this->ui->CancelAppointment->setText("Cancel");
        return;
    }
    int ownIndex = Find(ownID);
    (*usersRecords_ptr)[ownIndex].remove(AppointmentIndex + 2);
    QListWidgetItem *itemToRemove = ui->AppointmentsList->takeItem(AppointmentIndex - 1);
    (*usersRecords_ptr)[ownIndex][1] = QString::number((*usersRecords_ptr)[ownIndex].value(1).toInt() - 1);
    delete itemToRemove;
}

void doctor::on_AddAppointment_clicked()
{
    int ownIndex = Find(ownID);
    QString appointment = ui->AppointmentDate->toPlainText() + " " + "No Reservee";
    int recordNumber = (*usersRecords_ptr)[ownIndex].value(1).toInt();
    for (int i = 0; i < recordNumber; i++)
    {
        int recordIndex = i + 2;
        QString record = (*usersRecords_ptr)[ownIndex].value(recordIndex);

        QTextStream recordStream(&record);
        QString date;
        recordStream >> date;

        if (date == ui->AppointmentDate->toPlainText())
        {
            this->ui->AddAppointment->setText("Appointment at this time already exists");
            QEventLoop loop;
            QTimer::singleShot(1000, &loop, &QEventLoop::quit);
            loop.exec();
            this->ui->AddAppointment->setText("Add");
            return;
        }
    }

    (*usersRecords_ptr)[ownIndex].push_back(appointment);
    ui->AppointmentsList->addItem(appointment);
    (*usersRecords_ptr)[ownIndex][1] = QString::number((*usersRecords_ptr)[ownIndex].value(1).toInt() + 1);
}
