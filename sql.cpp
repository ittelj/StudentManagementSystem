#include "sql.h"
#include <QMessageBox>
#include <stdio.h>


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
        bool success=qSqlQuery->exec("create table IDPWInfo"
                                    "(id int primary key,"
                                    "password char(32))");
        if(success) qDebug("database table successfully created ");
        else qDebug("database table created failed ");
        qSqlQuery->exec("insert into IDPWInfo values(170101,'170101')");
        qSqlQuery->exec("insert into IDPWInfo values(170102,'170102')");
        qSqlQuery->exec("insert into IDPWInfo values(0,'admin')");
    }

}

SMSsqlDatabase::~SMSsqlDatabase()
{
    delete qSqlQuery;
    DB.close();
}

