#ifndef SQL_H
#define SQL_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class SMSsqlDatabase
{

public:
    explicit SMSsqlDatabase();
    ~SMSsqlDatabase();

private:
    QSqlDatabase DB;
    QSqlQuery* qSqlQuery;



};





#endif // SQL_H


