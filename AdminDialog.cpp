#include "AdminDialog.h"




AdminDialog::AdminDialog(SMSsqlDatabase* DB,QWidget *parent) :
    QDialog(parent)
{
    myDB=DB;
    setWindowTitle("administrator interface");
    setGeometry(350,120,1200,800);
    setWindowIcon(QIcon(":/icon.png"));
    gridLayout = new QGridLayout;
    vboxLayout = new QVBoxLayout;
    groupBoxChoice=new QGroupBox("please choose");
    groupBoxShowInfo=new QGroupBox("information"); 
    gridLayout->addWidget(groupBoxChoice,0,0,1,1);
    gridLayout->addWidget(groupBoxShowInfo,0,1,1,2);
    groupBoxChoice->setStyleSheet("QGroupBox {border: 1px solid gray;border-radius: 9px;margin-top: 0.5em;}QGroupBox::title {subcontrol-origin:margin;left: 10px;padding: 0 3px 0 3px;}");
    groupBoxShowInfo->setStyleSheet("QGroupBox {border: 1px solid gray;border-radius: 9px;margin-top: 0.5em;}QGroupBox::title {subcontrol-origin:margin;left: 10px;padding: 0 3px 0 3px;}");
    btnLogout= new QPushButton("log out system");
    btnAddInfo= new QPushButton("add information");
    btnManageInfo= new QPushButton("manage information");
    btnShowGradeInfo= new QPushButton("show grade information");
    btnLogout->resize(200,50);
    btnAddInfo->resize(200,50);
    btnManageInfo->resize(200,50);
    btnShowGradeInfo->resize(200,50);
    vboxLayout->addWidget(btnLogout);
    vboxLayout->addWidget(btnAddInfo);
    vboxLayout->addWidget(btnManageInfo);
    vboxLayout->addWidget(btnShowGradeInfo);
    stackLayout= new QStackedLayout;  
    welcomeLabel= new QLabel("welcome");
    welcomeLabel->setStyleSheet("color:rgb(255,170,0);font-size:190px;");
    stackLayout->addWidget(welcomeLabel);
    welcomeLabel->setContentsMargins(100,40,50,50);
    stackLayout->setCurrentIndex(0);

    addStudentInfoWidget= new addStudentInfo(myDB);
    stackLayout->addWidget(addStudentInfoWidget);
    addStudentInfoWidget->resize(900,700);
    addStudentInfoWidget->setContentsMargins(100,100,100,60);

    manageStudentInfoWidget= new manageStudentInfo(myDB);
    stackLayout->addWidget(manageStudentInfoWidget);
    manageStudentInfoWidget->resize(900,700);
    manageStudentInfoWidget->setContentsMargins(10,10,10,10);

    setLayout(gridLayout);
    groupBoxChoice->setLayout(vboxLayout);
    groupBoxShowInfo->setLayout(stackLayout);

    connect(btnLogout, SIGNAL(clicked()), this, SLOT(on_btnLogout_clicked()));
    connect(btnAddInfo, SIGNAL(clicked()), this, SLOT(on_btnAddInfo_clicked()));
    connect(btnManageInfo, SIGNAL(clicked()), this, SLOT(on_btnManageInfo_clicked()));
    connect(btnShowGradeInfo, SIGNAL(clicked()), this, SLOT(on_btnShowGradeInfo_clicked()));
}

AdminDialog::~AdminDialog()
{
    delete btnLogout;
    delete btnAddInfo;
    delete btnManageInfo;
    delete btnShowGradeInfo;
    delete welcomeLabel;
    delete addStudentInfoWidget;
    delete manageStudentInfoWidget;
    delete vboxLayout;
    delete stackLayout;
    delete gridLayout;
    delete groupBoxChoice;
    delete groupBoxShowInfo;

    qDebug("destruct AdminDialog\n");
}
void AdminDialog::on_btnLogout_clicked()
{
    qDebug("logout AdminDialog");
    this->close();
}
void AdminDialog::on_btnAddInfo_clicked()
{
    stackLayout->setCurrentIndex(1);
}
void AdminDialog::on_btnManageInfo_clicked()
{
    stackLayout->setCurrentIndex(2);
}
void AdminDialog::on_btnShowGradeInfo_clicked()
{
    stackLayout->setCurrentIndex(3);
}
