#ifndef SQL_H
#define SQL_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QStringList>

class SMSsqlDatabase
{

public:
    explicit SMSsqlDatabase();
    ~SMSsqlDatabase();
    int checkUserIDAndPassword(const QString &userID, const QString &password);
    int addStudentBaseInfo(QStringList &studentBaseInformation);
    QStringList comboBoxAddItems(QString tableName);


private:
    QSqlDatabase DB;
    QSqlQuery* qSqlQuery;
    QStringList tableItemStringlist;

};





#endif // SQL_H


