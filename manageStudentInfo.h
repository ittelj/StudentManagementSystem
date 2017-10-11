#ifndef MANAGESTUDENTINFO_H
#define MANAGESTUDENTINFO_H
#include <QWidget>
#include "sql.h"
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlTableModel>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>



class manageStudentInfo : public QWidget
{
    Q_OBJECT

public:
    explicit manageStudentInfo(SMSsqlDatabase* DB,QWidget *parent = 0);
    ~manageStudentInfo();

private:
    SMSsqlDatabase* myDB;
    QVBoxLayout* vBoxLayout;
    QHBoxLayout* hBoxLayoutTop;
    QHBoxLayout* hBoxLayoutBottom;
    QHBoxLayout* hBoxLayoutShow;
    QLabel* labelQueryMode;
    QLabel* labelQueryDetail;
    QComboBox* comboxQueryMode;
    QLineEdit* lineEditQueryDetail;
    QPushButton* btnOk;
    QPushButton* btnDelete;
    QPushButton* btnCommitChange;
    QSqlTableModel sqlTableMode;
    QTableView tableView;

private slots:
    void on_btnOk_clicked();
    void on_btnDelete_clicked();
    void on_btnCommitChange_clicked();

};



#endif // MANAGESTUDENTINFO_H

