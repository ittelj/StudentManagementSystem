#ifndef BTNADDINFO_H
#define BTNADDINFO_H
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class btnAddInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit btnAddInfoWidget(QWidget *parent = 0);
    ~btnAddInfoWidget();

private:
    QFormLayout* formLayout;
    QStringList labelStrings;
    QLabel qLabel[6];
    QLineEdit qLineEdit[6];
    QRegExp regExp[6];
    QPushButton* btnRegister;
    QPushButton* btnReset;
    QHBoxLayout* btnLayout;






};




#endif // BTNADDINFO_H

