#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <sql.h>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    SMSsqlDatabase* myDB;
    QGridLayout* gridLayout;
    QPushButton* btnLogin;
    QPushButton* btnCancel;
    QRadioButton* RbtnStu;
    QRadioButton* RbtnTch;
    QRadioButton* RbtnAdm;
    QLabel* userIDLabel;
    QLabel* userPWLabel;
    QLineEdit* userIDEdit;
    QLineEdit* userPWEdit;

    typedef enum{chUserID,chUserPW}inforCheckType;

    bool inputNotEmptyCheck(void);
    bool infoCheck(inforCheckType type);



private slots:
    void on_btnLogin_clicked();
    void on_btnCancel_clicked();
    //void on_btnAdm_clicked();
};

#endif // MAINWINDOW_H
