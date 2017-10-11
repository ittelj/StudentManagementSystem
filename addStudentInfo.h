#ifndef ADDSTUDENTINFO_H
#define ADDSTUDENTINFO_H
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QFile>
#include "sql.h"

class addStudentInfo : public QWidget
{
    Q_OBJECT

public:
    explicit addStudentInfo(SMSsqlDatabase* DB,QWidget *parent = 0);
    ~addStudentInfo();

private:
    SMSsqlDatabase* myDB;
    QFormLayout* formLayout;
    QStringList labelsText;
    QLabel Labels[6];
    QRegExp regExp[2];
    QLineEdit* LineEditID;
    QLineEdit* LineEditName;
    QComboBox* comboBoxSex;
    QDateEdit* dateEditBirth;
    QComboBox* comboBoxMajor;
    QComboBox* comboBoxClass;
    QPushButton* btnRegister;
    QPushButton* btnReset;
    QPushButton* btnImport;
    QHBoxLayout* btnLayout;

private slots:
    void on_btnRegister_clicked();
    void on_btnReset_clicked();
    void on_btnImport_clicked();

};


#endif // ADDSTUDENTINFO_H

