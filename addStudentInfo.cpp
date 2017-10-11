#include "addStudentInfo.h"
#include <QFileDialog>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

addStudentInfo::addStudentInfo(SMSsqlDatabase* DB,QWidget *parent) :
    QWidget(parent)
{
    myDB= DB;
    formLayout=new QFormLayout; 
    labelsText << "ID number:" << "name:" << "sex:" << " birth date:"<< "majorID:"<< "classID:";
    int i;
    for(i=0;i<6;i++)
    {
        Labels[i].setText(labelsText[i]);
        Labels[i].resize(100,70);
    }

    LineEditID = new QLineEdit;
    LineEditID->setPlaceholderText("example:170101(17:register year,01:class number,01:student number)");
    regExp[0].setPattern("^[0-9]{6}$");
    LineEditID->setValidator(new QRegExpValidator(regExp[0],this));
    LineEditID->resize(400,70);
    formLayout->addRow(&Labels[0],LineEditID);

    LineEditName = new QLineEdit;
    LineEditName->setPlaceholderText("example:Luojiaojiao");
    regExp[1].setPattern("^[a-zA-Z]{1,20}$");
    LineEditName->setValidator(new QRegExpValidator(regExp[1],this));
    LineEditName->resize(400,70);
    formLayout->addRow(&Labels[1],LineEditName);

    comboBoxSex = new QComboBox;
    comboBoxSex->addItem("female");
    comboBoxSex->addItem("male");
    comboBoxSex->resize(400,70);
    formLayout->addRow(&Labels[2],comboBoxSex);

    dateEditBirth = new QDateEdit;
    dateEditBirth->setCalendarPopup(true);
    dateEditBirth->resize(400,70);
    dateEditBirth->setDisplayFormat("yyyy-MM-dd");
    formLayout->addRow(&Labels[3],dateEditBirth);

    comboBoxMajor = new QComboBox;
    comboBoxMajor->addItems(myDB->comboBoxAddItems("majorInfo"));  /*call the database information*/
    comboBoxMajor->resize(400,70);
    formLayout->addRow(&Labels[4],comboBoxMajor);

    comboBoxClass = new QComboBox;
    comboBoxClass->addItems(myDB->comboBoxAddItems("classInfo"));  /*call the database information*/
    comboBoxClass->resize(400,70);
    formLayout->addRow(&Labels[5],comboBoxClass);

    formLayout->setLabelAlignment(Qt::AlignRight);
    formLayout->setSpacing(40);
    setLayout(formLayout);

    btnRegister=new QPushButton("register");
    btnReset=new QPushButton("reset");
    btnImport=new QPushButton("import");
    btnRegister->resize(100,70);
    btnReset->resize(100,70);
    btnImport->resize(100,70);

    btnLayout=new QHBoxLayout;
    btnLayout->setSpacing(60);
    btnLayout->setContentsMargins(60,30,80,50);
    btnLayout->addWidget(btnRegister);
    btnLayout->addWidget(btnReset);
    btnLayout->addWidget(btnImport);
    formLayout->addRow(btnLayout);

    connect(btnRegister, SIGNAL(clicked()), this, SLOT(on_btnRegister_clicked()));
    connect(btnReset, SIGNAL(clicked()), this, SLOT(on_btnReset_clicked()));
    connect(btnImport, SIGNAL(clicked()), this, SLOT(on_btnImport_clicked()));
}
addStudentInfo::~addStudentInfo()
{
    delete LineEditID;
    delete LineEditName;
    delete comboBoxSex;
    delete dateEditBirth;
    delete comboBoxMajor;
    delete comboBoxClass;
    delete btnRegister;
    delete btnReset;
    delete btnImport;
    delete btnLayout;
    delete formLayout;

    qDebug("destruct addStudentInfo\n");
}

void addStudentInfo::on_btnRegister_clicked()
{
    QStringList studentBaseInfo;
    QDate date=dateEditBirth->date();
    QStringList majorItemList;
    majorItemList= comboBoxMajor->currentText().split("   "); /*string to stringlist*/
    QStringList classItemList;
    classItemList= comboBoxMajor->currentText().split("   "); /*string to stringlist*/

    studentBaseInfo<< LineEditID->text()<< LineEditName->text()<< comboBoxSex->currentText()
                   << date.toString(Qt::ISODate)<< majorItemList[0]<< classItemList[0];
    switch(myDB->addStudentBaseInfo(studentBaseInfo))
    {
        case 0:
            QMessageBox::information(this,"information","add information successed!");
            break;
        case 1:
            QMessageBox::warning(this,"warning","add information failed!");
            break;
        default:
            QMessageBox::warning(this,"warning","stuID has exist!");
    }
}
void addStudentInfo::on_btnReset_clicked()
{
    LineEditID->clear();
    LineEditName->clear();
}
void addStudentInfo::on_btnImport_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this,"open file", ".");
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setGeometry(10,30,200,100);
    QFile file;
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QStringList path = fileDialog->selectedFiles();
        qDebug()<< path;
        QString filePath = path[0];
        qDebug()<< filePath;
        file.setFileName(filePath);
        if (file.open(QIODevice::ReadOnly))
        {
            qDebug("open file successed!");
        }
    }

    QString stringReadLine;
    QStringList stringListReadLine;
    QString successedInfo;
    QString failedInfo;
    QString existInfo;
    while(!file.atEnd())
    {
        stringReadLine = file.readLine();
        stringListReadLine = stringReadLine.split(",");
        qDebug()<< stringListReadLine;
        switch(myDB->addStudentBaseInfo(stringListReadLine))
        {
            case 0:
                successedInfo.append(stringListReadLine[0]);
                successedInfo.append(",");
                break;
            case 1:
                failedInfo.append(stringListReadLine[0]);
                failedInfo.append(",");
                break;
            default:

                existInfo.append(stringListReadLine[0]);
                existInfo.append(",");
        }
    }

    if(0 != failedInfo.size())
    {
        failedInfo.append("add failed");
        QMessageBox::warning(this,"warning",failedInfo);
    }
    if(0 != existInfo.size())
    {
        existInfo.append("has exist");
        QMessageBox::warning(this,"warning",existInfo);
    }
    if((0 == failedInfo.size()) && (0 == existInfo.size()))
    {
        QMessageBox::information(this,"information","add all information successed!");
    }

}

