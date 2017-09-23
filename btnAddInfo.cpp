#include "btnAddInfo.h"
#include <QRegExpValidator>

btnAddInfoWidget::btnAddInfoWidget(QWidget *parent) :
    QWidget(parent)
{
    formLayout=new QFormLayout;
    setLayout(formLayout);
    QStringList labels;
    labels << "ID number:" << "name:" << "sex:" << " birth date:"<< "major:"<< "class:";
    int i;
    for(i=0;i<6;i++)
    {
        qLabel[i].setText(labels[i]);
        qLabel[i].setFixedSize(100,40);
        qLineEdit[i].setFixedSize(400,40);
        formLayout->addRow(&qLabel[i],&qLineEdit[i]);
    }
    qLineEdit[0].setPlaceholderText("example:170101(17:register year,01:class number,01:student number)");
    regExp[0].setPattern("^[0-9]{6}$");
    qLineEdit[0].setValidator(new QRegExpValidator(regExp[0],this));

    qLineEdit[1].setPlaceholderText("example:Luojiaojiao");
    regExp[1].setPattern("^[a-zA-Z]{1,20}$");
    qLineEdit[1].setValidator(new QRegExpValidator(regExp[1],this));

    qLineEdit[2].setPlaceholderText("choose sex");
    regExp[2].setPattern("^[a-zA-Z]{1,20}$");
    qLineEdit[2].setValidator(new QRegExpValidator(regExp[2],this));

    qLineEdit[3].setInputMask("0000-00-00");

    qLineEdit[4].setPlaceholderText("choose sex");
    regExp[4].setPattern("^[a-zA-Z]{1,20}$");
    qLineEdit[4].setValidator(new QRegExpValidator(regExp[4],this));

    qLineEdit[5].setPlaceholderText("choose sex");
    regExp[5].setPattern("^[a-zA-Z]{1,20}$");
    qLineEdit[5].setValidator(new QRegExpValidator(regExp[5],this));

    formLayout->setLabelAlignment(Qt::AlignRight);
    btnRegister=new QPushButton;
    btnReset=new QPushButton;
    btnRegister->setFixedSize(60,40);
    btnReset->setFixedSize(60,40);
    btnLayout=new QHBoxLayout;
    btnLayout->setSpacing(40);
    btnLayout->setContentsMargins(200,60,100,60);
    btnLayout->addWidget(btnRegister);
    btnLayout->addWidget(btnReset);
    formLayout->addRow(btnLayout);


}
btnAddInfoWidget::~btnAddInfoWidget()
{

}
