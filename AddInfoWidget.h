#ifndef BTNADDINFO_H
#define BTNADDINFO_H
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include "sql.h"

class AddInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddInfoWidget(SMSsqlDatabase* DB,QWidget *parent = 0);
    ~AddInfoWidget();

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
    QHBoxLayout* btnLayout;

private slots:
    void on_btnRegister_clicked();
    void on_btnReset_clicked();






};




#endif // BTNADDINFO_H

