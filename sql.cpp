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
        qSqlQuery->prepare("insert into courseInfo values(?,?)");
        QVariantList courseCodes;
        courseCodes<< "JSJ001" << "JSJ002" << "JSJ003" << "JSJ004" << "JSJ005"
                   << "JSJ006" << "JSJ007" << "JSJ008" << "JSJ009";
        qSqlQuery->addBindValue(courseCodes);
        QVariantList courseNames;
        courseNames << "Programming Foundations" << "College Physics" << "Operating System"
                   << "Computer Network" << "Assembly Language" << "Java Language"
                   << "Linear Algebra" << "Higher Mathematics" << "College English";
        qSqlQuery->addBindValue(courseNames);
        if (!qSqlQuery->execBatch())
            qDebug("execBatch failed");

        bool success4 = qSqlQuery->exec("create table majorInfo"
                        "(majorCode char(16) primary key not null,"  /*majorCode:A010101,A01:一级学科代码,01:二级学科代码,*/
                        "majorName char(128) not null)");
        if(success4) qDebug("majorInfo database table successfully created ");
        else qDebug("majorInfo database table created failed ");
        qSqlQuery->prepare("insert into majorInfo values(?,?)");
        QVariantList majorCodes;
        majorCodes<< "A010101" << "A010102" << "A010103" << "A010104" << "A010105"
                   << "A010106" << "A010107" << "A010108" << "A010109";
        qSqlQuery->addBindValue(majorCodes);
        QVariantList majorNames;
        majorNames << "Computer Science and Technology" << "Mechanical Engineering" << "Communication Engineering"
                   << "Financial Management" << "Civil Engineering" << "Industrial Design"
                   << "Automobile Orientation" << "Chemistry Engineering and Technology" << "Information and computer science";
        qSqlQuery->addBindValue(majorNames);
        if (!qSqlQuery->execBatch())
            qDebug("execBatch failed");

        bool success5 = qSqlQuery->exec("create table classInfo"
                        "(classCode char(16) primary key not null,"  /*classCode:17JSJ0101,17:register year,JSJ:institute,01:major,*/
                        "className char(128) not null)");
        if(success5) qDebug("classInfo database table successfully created ");
        else qDebug("classInfo database table created failed ");
        qSqlQuery->prepare("insert into classInfo values(?,?)");
        QVariantList classCodes;
        classCodes << "17JSJ0101" << "17JSJ0102" << "17JSJ0103";
        qSqlQuery->addBindValue(classCodes);
        QVariantList classNames;
        classNames << "Computer Science and Technology classNo.1" << "Computer Science and Technology classNo.2"
                  << "Computer Science and Technology classNo.3";
        qSqlQuery->addBindValue(classNames);
        if (!qSqlQuery->execBatch())
            qDebug("execBatch failed");
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
    qSqlQuery->prepare("SELECT * FROM IDPWINFO WHERE id=? and password=?;");
    qSqlQuery->bindValue(0,QVariant(userID.toInt()));
    qSqlQuery->bindValue(1,password);
    qSqlQuery->exec();
    QSqlRecord rec = qSqlQuery->record();

    qDebug() << "checkUserIDAndPassword Number of columns: " << rec.count();
    while (qSqlQuery->next())
        qDebug() << qSqlQuery->value(0).toString()<< qSqlQuery->value(1).toString()<<qSqlQuery->value(2).toString(); // output all names

    if(qSqlQuery->first())
    {
        result = qSqlQuery->value(2).toInt();
    }
    return result;
}

int SMSsqlDatabase::addStudentBaseInfo(QStringList &studentBaseInformation)
{
    int result= -1;
    qSqlQuery->prepare("SELECT id FROM stuBaseInfo WHERE id=?;");
    qSqlQuery->bindValue(0,QVariant(studentBaseInformation[0].toInt()));
    qSqlQuery->exec();
    QSqlRecord rec = qSqlQuery->record();
    while (qSqlQuery->next())
    {
        qDebug() << "addStudentBaseInfo Number of columns: " << rec.count();
        qDebug() << qSqlQuery->value(0).toInt();
    }
    if(!qSqlQuery->first())  /*stuID doesn't exist*/
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

        if(qSqlQuery->exec())
        {
            result= 0;
        }
        else
        {
            result= 1;
        }
    }
    return result;
}

QStringList SMSsqlDatabase::comboBoxAddItems(QString tableName)
{
    QString stringExec = "SELECT * FROM ";
    stringExec.append(tableName);
    stringExec.append(";");
    qDebug() << stringExec;
    qSqlQuery->exec(stringExec);
    QSqlRecord rec = qSqlQuery->record();
    qDebug() << "comboBoxAddItemsMajor Number of columns: " << rec.count();
    QString temp;
    tableItemStringlist.clear();
    while (qSqlQuery->next())
    {
        qDebug() << qSqlQuery->value(0).toString()<< qSqlQuery->value(1).toString(); // output all names
        temp= (qSqlQuery->value(0).toString());
        temp.append("   "); /*3 space*/
        temp.append(qSqlQuery->value(1).toString());
        tableItemStringlist << temp;
    }
    return tableItemStringlist;
}
