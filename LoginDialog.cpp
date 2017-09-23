#include "LoginDialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QTextStream>
#include <assert.h>
#include "AdminDialog.h"



LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    myDB= new SMSsqlDatabase();
    setWindowTitle("student management system log in interface");
    setGeometry(600,150,600,400);
    setWindowIcon(QIcon(":/icon.png"));
    userIDLabel= new QLabel;
    userPWLabel= new QLabel;
    userIDEdit= new QLineEdit;
    userPWEdit= new QLineEdit;
    userIDLabel->setText("user ID:");
    userPWLabel->setText("user password:");
    userIDEdit->setFixedSize(300,40);
    userPWEdit->setFixedSize(300,40);
    userPWEdit->setEchoMode(QLineEdit::Password);
    QRegExp regID;
    QRegExp regPW;
    userIDEdit->setPlaceholderText("example:170101");
    regID.setPattern("^[0-9]{6}$");
    userIDEdit->setValidator(new QRegExpValidator(regID,this));
    userPWEdit->setPlaceholderText("password");
    regPW.setPattern("^[A-Za-z0-9]{6,18}$");
    userPWEdit->setValidator(new QRegExpValidator(regPW,this)); 
    RbtnStu=new QRadioButton("student");
    RbtnTch=new QRadioButton("teacher");
    RbtnAdm=new QRadioButton("administrator");
    btnLogin= new QPushButton("login");
    btnCancel= new QPushButton("cancel");
    btnLogin->setFixedSize(100,50);
    btnCancel->setFixedSize(100,50);
    RbtnStu->setChecked(true);

    gridLayout= new QGridLayout;
    gridLayout->addWidget(userIDLabel,0,0,1,1,Qt::AlignRight);
    gridLayout->addWidget(userPWLabel,1,0,1,1,Qt::AlignRight);
    gridLayout->addWidget(RbtnStu,2,0,1,1,Qt::AlignRight);
    gridLayout->addWidget(btnLogin,3,0,1,1,Qt::AlignRight);
    gridLayout->addWidget(userIDEdit,0,1,1,2);
    gridLayout->addWidget(userPWEdit,1,1,1,2);
    gridLayout->addWidget(RbtnTch,2,1,1,1,Qt::AlignCenter);
    gridLayout->addWidget(RbtnAdm,2,2,1,1,Qt::AlignLeft);
    gridLayout->addWidget(btnCancel,3,2,1,1,Qt::AlignLeft);
    gridLayout->setHorizontalSpacing(10);
    gridLayout->setVerticalSpacing(10);
    gridLayout->setContentsMargins(5,40,15,30);
    setLayout(gridLayout);

    connect(btnLogin, SIGNAL(clicked()), this, SLOT(on_btnLogin_clicked()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(on_btnCancel_clicked()));
}

LoginDialog::~LoginDialog()
{
    delete myDB;
    delete gridLayout;
    delete btnLogin;
    delete btnCancel;
    delete RbtnStu;
    delete RbtnTch;
    delete RbtnAdm;
    delete userIDLabel;
    delete userPWLabel;
    delete userIDEdit;
    delete userPWEdit;
    qDebug("~logindialog\n");
}
void LoginDialog::on_btnLogin_clicked()
{
    if(inputNotEmptyCheck())
    {
        if(RbtnStu->isChecked())    /*student identity*/
        {

        }
        else if(RbtnTch->isChecked())   /*teacher identity*/
        {

        }
        else    /*RbtnAdm->isChecked() admin identity*/
        {

        }
        if(infoCheck(chUserID))
        {
            if(infoCheck(chUserPW))
            {
                AdminDialog AdministratorDialog;
                this->setVisible(false);
                AdministratorDialog.exec();
                //QMessageBox::warning(this,"warning","success!");
            }
        }
    }
}
void LoginDialog::on_btnCancel_clicked()
{
    this->close();
}

bool LoginDialog::inputNotEmptyCheck(void)
{
    if(userIDEdit->text().isEmpty()|| userPWEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"warning","userID and password cant't be empty!");
        return false;
    }
    else if((RbtnStu->isChecked()== false) && (RbtnTch->isChecked()== false)&& (RbtnAdm->isChecked()== false))
    {
       QMessageBox::warning(this,"warning","must choose your identity!");
       return false;
    }
    else
    {
        return true;
    }
}
bool LoginDialog::infoCheck(inforCheckType type)
{
    bool result;
    const char* fileADDr;
    QString warningInfo;
    int findFlag;
    switch(type)
    {
        case chUserID:
            fileADDr="/home/parai/workspace/c_study/QT_study/StudentManagementSystem/StudentManagementSystem/studentID.txt";
            warningInfo="the student ID does't exist!";
            break;
        case chUserPW:
            fileADDr="/home/parai/workspace/c_study/QT_study/StudentManagementSystem/StudentManagementSystem/studentPW.txt";
            warningInfo="password is wrong!";
            break;
    }
    FILE *fp=fopen(fileADDr,"r");
    assert(fp!=NULL);
    if(feof(fp)== 0)
    {
        QTextStream qtestStr(fp);
        QString str=qtestStr.readAll();
        QStringList strList=str.split('\n');
        QListIterator<QString> listIte(strList);
        while(listIte.hasNext())
        {
            if(userIDEdit->text()==listIte.next())
            {
                findFlag=true;
                break;
            }
        }
        if(findFlag== true)
        {
           result= true;
        }
        else
        {
            QMessageBox::warning(this,"warning",warningInfo);
            result= false;
        }
    }
    fclose(fp);
    return result;
}
