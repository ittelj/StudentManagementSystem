#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H
#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include "sql.h"


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
    QPushButton* btnDeleInfo;
    QPushButton* btnChangeInfo;
    QPushButton* btnShowBaseInfo;
    QPushButton* btnShowGradeInfo;
    QStackedLayout* stackLayout;


private slots:
    void on_btnLogout_clicked();
    void on_btnAddInfo_clicked();
    void on_btnDeleInfo_clicked();
    void on_btnChangeInfo_clicked();
    void on_btnShowBaseInfo_clicked();
    void on_btnShowGradeInfo_clicked();
};



#endif // ADMINISTRATOR_H

