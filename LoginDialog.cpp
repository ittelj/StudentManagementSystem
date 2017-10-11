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
    userIDLabel= new QLabel("user ID:");
    userPWLabel= new QLabel("user password:");
    userIDEdit= new QLineEdit;
    userPWEdit= new QLineEdit;
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
    btnLogin= new QPushButton("login");
    btnCancel= new QPushButton("cancel");
    btnLogin->setFixedSize(100,50);
    btnCancel->setFixedSize(100,50);

    gridLayout= new QGridLayout;
    gridLayout->addWidget(userIDLabel,0,0,1,1,Qt::AlignRight);
    gridLayout->addWidget(userPWLabel,1,0,1,1,Qt::AlignRight);
    gridLayout->addWidget(btnLogin,2,0,1,1,Qt::AlignRight);
    gridLayout->addWidget(userIDEdit,0,1,1,2);
    gridLayout->addWidget(userPWEdit,1,1,1,2);
    gridLayout->addWidget(btnCancel,2,2,1,1,Qt::AlignLeft);
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
    delete btnLogin;
    delete btnCancel;
    delete userIDLabel;
    delete userPWLabel;
    delete userIDEdit;
    delete userPWEdit;
    delete gridLayout;
    qDebug("destruct logindialog\n");
}
void LoginDialog::on_btnLogin_clicked()
{
    if(inputNotEmptyCheck())
    {

        switch(myDB->checkUserIDAndPassword(userIDEdit->text(), userPWEdit->text()))    /*0:student,1:teacher,2:admin*/
        {
            case 0:
            break;
            case 1:
            break;
            case 2:
            {
                AdminDialog AdministratorDialog(myDB);
                this->setVisible(false);
                AdministratorDialog.exec();
                this->setVisible(true);
                break;
            }
            default:
                QMessageBox::warning(this,"warning","userID and password doesn't match!");
                break;
        }
    }

}
void LoginDialog::on_btnCancel_clicked()
{
    this->close();
}

bool LoginDialog::inputNotEmptyCheck(void)
{
    bool result = false;
    if(userIDEdit->text().isEmpty()|| userPWEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"warning","userID and password cant't be empty!");
    }
    else
    {
        result = true;
    }
    return result;
}
