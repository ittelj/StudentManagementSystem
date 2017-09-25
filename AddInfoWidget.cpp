#include "AddInfoWidget.h"

#include <QRegExpValidator>
#include <QMessageBox>
#include <QDate>

AddInfoWidget::AddInfoWidget(SMSsqlDatabase* DB,QWidget *parent) :
    QWidget(parent)
{
    myDB= DB;
    formLayout=new QFormLayout;
    setLayout(formLayout);
    labelsText << "ID number:" << "name:" << "sex:" << " birth date:"<< "majorID:"<< "classID:";
    int i;
    for(i=0;i<6;i++)
    {
        Labels[i].setText(labelsText[i]);
        Labels[i].setFixedSize(100,50);
    }

    LineEditID = new QLineEdit;
    LineEditID->setPlaceholderText("example:170101(17:register year,01:class number,01:student number)");
    regExp[0].setPattern("^[0-9]{6}$");
    LineEditID->setValidator(new QRegExpValidator(regExp[0],this));
    LineEditID->setFixedSize(450,50);
    formLayout->addRow(&Labels[0],LineEditID);

    LineEditName = new QLineEdit;
    LineEditName->setPlaceholderText("example:Luojiaojiao");
    regExp[1].setPattern("^[a-zA-Z]{1,20}$");
    LineEditName->setValidator(new QRegExpValidator(regExp[1],this));
    LineEditName->setFixedSize(450,50);
    formLayout->addRow(&Labels[1],LineEditName);

    comboBoxSex = new QComboBox;
    comboBoxSex->addItem("female");
    comboBoxSex->addItem("male");
    comboBoxSex->setFixedSize(450,50);
    formLayout->addRow(&Labels[2],comboBoxSex);

    dateEditBirth = new QDateEdit(QDate::currentDate());
    dateEditBirth->setCalendarPopup(true);
    dateEditBirth->setFixedSize(450,50);
    dateEditBirth->setDisplayFormat("yyyy-MM-dd");
    formLayout->addRow(&Labels[3],dateEditBirth);

    comboBoxMajor = new QComboBox;
    comboBoxMajor->addItem("A010101");
    comboBoxMajor->addItem("A010102");
    comboBoxMajor->addItem("A010103");
    comboBoxMajor->setFixedSize(450,50);
    formLayout->addRow(&Labels[4],comboBoxMajor);

    comboBoxClass = new QComboBox;
    comboBoxClass->addItem("17JSJ0101");
    comboBoxClass->addItem("17JSJ0102");
    comboBoxClass->addItem("17JSJ0103");
    comboBoxClass->setFixedSize(450,50);
    formLayout->addRow(&Labels[5],comboBoxClass);

    formLayout->setLabelAlignment(Qt::AlignRight);
    formLayout->setSpacing(30);
    btnRegister=new QPushButton("register");
    btnReset=new QPushButton("reset");
    btnRegister->setFixedSize(80,40);
    btnReset->setFixedSize(80,40);

    btnLayout=new QHBoxLayout;
    btnLayout->setSpacing(60);
    btnLayout->setContentsMargins(60,30,80,50);
    btnLayout->addWidget(btnRegister);
    btnLayout->addWidget(btnReset);
    formLayout->addRow(btnLayout);

    connect(btnRegister, SIGNAL(clicked()), this, SLOT(on_btnRegister_clicked()));
    connect(btnReset, SIGNAL(clicked()), this, SLOT(on_btnReset_clicked()));


}
AddInfoWidget::~AddInfoWidget()
{
    delete formLayout;
    delete LineEditID;
    delete LineEditName;
    delete comboBoxSex;
    delete dateEditBirth;
    delete comboBoxMajor;
    delete comboBoxClass;
    delete btnRegister;
    delete btnReset;
    delete btnLayout;
}

void AddInfoWidget::on_btnRegister_clicked()
{
    QStringList studentBaseInfo;
    QDate date=dateEditBirth->date();

    studentBaseInfo<< LineEditID->text()<< LineEditName->text()<< comboBoxSex->currentText()
                   << date.toString(Qt::ISODate)<< comboBoxMajor->currentText()<< comboBoxClass->currentText();
    /*
    studentBaseInfo[0]= LineEditID->text();
    studentBaseInfo[1]=LineEditName->text();
    studentBaseInfo[2]=comboBoxSex->currentText();
    QDate date=dateEditBirth->date();
    studentBaseInfo[3]=date.toString(Qt::ISODate);
    studentBaseInfo[4]=comboBoxMajor->currentText();
    studentBaseInfo[5]=comboBoxClass->currentText();
    */

    if(myDB->addStudentBaseInfo(studentBaseInfo))
    {
        QMessageBox::information(this,"information","add information successed!");
    }
    else
    {
        QMessageBox::warning(this,"warning","add information failed!");
    }

}
void AddInfoWidget::on_btnReset_clicked()
{

}
