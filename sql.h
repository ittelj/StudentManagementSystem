#ifndef SQL_H
#define SQL_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

class SMSsqlDatabase
{

public:
    explicit SMSsqlDatabase();
    ~SMSsqlDatabase();
    int checkUserIDAndPassword(const QString &userID, const QString &password);
    bool addStudentBaseInfo(QStringList &studentBaseInformation);



private:
    QSqlDatabase DB;
    QSqlQuery* qSqlQuery;



};





#endif // SQL_H


