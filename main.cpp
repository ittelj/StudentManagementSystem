#include "LoginDialog.h"
#include <QApplication>
#include <QtGui>
#include "sql.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog w;
    w.show();






    return a.exec();
}
