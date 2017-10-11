#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H
#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLabel>
#include "sql.h"
#include "addStudentInfo.h"
#include "manageStudentInfo.h"


class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(SMSsqlDatabase* DB,QWidget *parent = 0);
    ~AdminDialog();

private:
    SMSsqlDatabase* myDB;
    QGridLayout* gridLayout;
    QVBoxLayout* vboxLayout;
    QGroupBox* groupBoxChoice;
    QGroupBox* groupBoxShowInfo;
    QPushButton* btnLogout;
    QPushButton* btnAddInfo;
    QPushButton* btnManageInfo;
    QPushButton* btnShowGradeInfo;
    QStackedLayout* stackLayout;
    QLabel* welcomeLabel;
    addStudentInfo* addStudentInfoWidget;
    manageStudentInfo* manageStudentInfoWidget;


private slots:
    void on_btnLogout_clicked();
    void on_btnAddInfo_clicked();
    void on_btnManageInfo_clicked();
    void on_btnShowGradeInfo_clicked();
};



#endif // ADMINISTRATOR_H

