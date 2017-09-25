#include "sql.h"
#include <QMessageBox>
#include <stdio.h>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>

SMSsqlDatabase::SMSsqlDatabase():DB(QSqlDatabase::addDatabase("QSQLITE"))
{
    FILE* pf=fopen("smsDB.db","r");
    bool existFlag=false;

    if(pf != NULL)
    {
        existFlag= true;
        fclose(pf);
    }

    DB.setDatabaseName("smsDB.db");
    DB.setUserName("administrator");
    DB.setPassword("administrator");

    if(!DB.open())
    {
         QMessageBox::warning(NULL,"warning","open database failed!");
    }

    qSqlQuery=new QSqlQuery;

    if(false == existFlag)
    {
        bool success1 = qSqlQuery->exec("create table IDPWInfo"
                                    "(id int primary key not null,"
                                    "password char(32) not null,"
                                     "type int not null)");/*type:0:student,1:teacher,2:admin*/
        if(success1) qDebug("IDPWInfo database table successfully created ");
        else qDebug("IDPWInfo database table created failed ");
        qSqlQuery->exec("insert into IDPWInfo values(170101,'170101',0)");
        qSqlQuery->exec("insert into IDPWInfo values(170102,'170102',0)");
        qSqlQuery->exec("insert into IDPWInfo values(0,'admin',2)");

        bool success2 = qSqlQuery->exec("create table stuBaseInfo"
                        "(id int primary key not null,"  /*170101:17:register year,01:class number,01:student number*/
                        "type int not null,"
                        "name char(64) not null,"
                        "sex char(8) not null,"
                        "birthDate date not null,"
                        "majorCode char(16) not null,"  /*majorCode:A010101,A01:一级学科代码,01:二级学科代码,*/
                        "classCode char(16) not null)");/*classCode:17JSJ0101,17:register year,JSJ:institute,01:major,*/
        if(success2) qDebug("stuBaseInfo database table successfully created ");
        else qDebug("stuBaseInfo database table created failed ");
        qSqlQuery->exec("insert into stuBaseInfo values(170101,0,'luojiaojiao','female','1991-11-03','A010101','17JSJ0101')");

        bool success3 = qSqlQuery->exec("create table courseInfo"
                        "(courseCode char(16) primary key not null,"  /*JSJ001;JSJ:institute*/
                        "courseName char(128) not null)");
        if(success3) qDebug("courseInfo database table successfully created ");
        else qDebug("courseInfo database table created failed ");
        qSqlQuery->exec("insert into courseInfo values('JSJ001','Programming Foundations')");
        qSqlQuery->exec("insert into courseInfo values('JSJ002','College Physics')");
        qSqlQuery->exec("insert into courseInfo values('JSJ003','Operating System')");
        qSqlQuery->exec("insert into courseInfo values('JSJ004','Computer Network')");
        qSqlQuery->exec("insert into courseInfo values('JSJ005','Assembly Language')");
        qSqlQuery->exec("insert into courseInfo values('JSJ006','Java Language')");
        qSqlQuery->exec("insert into courseInfo values('JSJ007','Linear Algebra')");
        qSqlQuery->exec("insert into courseInfo values('JSJ008','Higher Mathematics')");
        qSqlQuery->exec("insert into courseInfo values('JSJ009','College English')");
    }
}

SMSsqlDatabase::~SMSsqlDatabase()
{
    delete qSqlQuery;
    DB.close();
}
int SMSsqlDatabase::checkUserIDAndPassword(const QString &userID, const QString &password)
{
    int result=-1;
    qSqlQuery->prepare("SELECT * FROM IDPWINFO"
                       " WHERE id=? and password=?;");
    qSqlQuery->bindValue(0,QVariant(userID.toInt()));
    qSqlQuery->bindValue(1,password);
    qSqlQuery->exec();
    QSqlRecord rec = qSqlQuery->record();

    qDebug() << "Number of columns: " << rec.count();
    while (qSqlQuery->next())
        qDebug() << qSqlQuery->value(0).toString()<< qSqlQuery->value(1).toString()<<qSqlQuery->value(2).toString(); // output all names

    if(qSqlQuery->first())
    {
        result = qSqlQuery->value(2).toInt();
    }
    else
    {
        result = -1;
    }

    return result;
}

bool SMSsqlDatabase::addStudentBaseInfo(QStringList &studentBaseInformation)
{
    qSqlQuery->prepare("INSERT INTO stuBaseInfo (id,type,name,sex,birthDate,majorCode,classCode) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    qSqlQuery->bindValue(0,QVariant(studentBaseInformation[0].toInt()));
    qSqlQuery->bindValue(1,0);
    qSqlQuery->bindValue(2,studentBaseInformation[1]);
    qSqlQuery->bindValue(3,studentBaseInformation[2]);
    qSqlQuery->bindValue(4,studentBaseInformation[3]);
    qSqlQuery->bindValue(5,studentBaseInformation[4]);
    qSqlQuery->bindValue(6,studentBaseInformation[5]);
    return qSqlQuery->exec();
}
