#include "manageStudentInfo.h"
#include <QDebug>
#include <QMessageBox>
#include <QItemSelectionModel>
#include <QModelIndexList>

manageStudentInfo::manageStudentInfo(SMSsqlDatabase* DB,QWidget *parent) :
    QWidget(parent)
{
    myDB= DB;
    vBoxLayout= new QVBoxLayout;
    hBoxLayoutTop=new QHBoxLayout;
    hBoxLayoutBottom=new QHBoxLayout;
    hBoxLayoutShow=new QHBoxLayout;
    vBoxLayout->setStretchFactor(hBoxLayoutTop,3);
    vBoxLayout->setStretchFactor(hBoxLayoutBottom,3);
    vBoxLayout->setStretchFactor(hBoxLayoutShow,50);
    labelQueryMode= new QLabel("please choose query mode:");
    labelQueryDetail= new QLabel("please input details:");
    comboxQueryMode= new QComboBox;
    lineEditQueryDetail= new QLineEdit;
    btnOk= new QPushButton("ok");
    btnDelete= new QPushButton("delete");
    btnCommitChange= new QPushButton("commit change");
    hBoxLayoutTop->addWidget(labelQueryMode);
    hBoxLayoutTop->addWidget(comboxQueryMode);
    hBoxLayoutTop->addWidget(labelQueryDetail);
    hBoxLayoutTop->addWidget(lineEditQueryDetail);
    hBoxLayoutTop->addWidget(btnOk);
    hBoxLayoutBottom->addWidget(btnDelete);
    hBoxLayoutBottom->addWidget(btnCommitChange);
    comboxQueryMode->addItem("student id");
    comboxQueryMode->addItem("student name");
    comboxQueryMode->addItem("majorCode");
    comboxQueryMode->addItem("classCode");
    labelQueryMode->resize(300,50);
    labelQueryDetail->resize(300,50);
    comboxQueryMode->resize(100,60);
    lineEditQueryDetail->resize(100,60);

    sqlTableMode.setTable("stuBaseInfo");
    sqlTableMode.setEditStrategy(QSqlTableModel::OnManualSubmit);
    sqlTableMode.removeColumn(1);
    sqlTableMode.select();

    hBoxLayoutShow->addWidget(&tableView);
    tableView.setModel(&sqlTableMode);
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked);
    tableView.show();

    setLayout(vBoxLayout);
    vBoxLayout->addLayout(hBoxLayoutTop);
    vBoxLayout->addLayout(hBoxLayoutShow);
    vBoxLayout->addLayout(hBoxLayoutBottom);
    vBoxLayout->setSpacing(10);
    hBoxLayoutTop->setSpacing(30);

    connect(btnOk, SIGNAL(clicked()), this, SLOT(on_btnOk_clicked()));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(on_btnDelete_clicked()));
    connect(btnCommitChange, SIGNAL(clicked()), this, SLOT(on_btnCommitChange_clicked()));
}

manageStudentInfo::~manageStudentInfo()
{

    delete labelQueryMode;
    delete labelQueryDetail;
    delete comboxQueryMode;
    delete lineEditQueryDetail;
    delete btnOk;
    delete btnDelete;
    delete btnCommitChange;
    delete hBoxLayoutTop;
    delete hBoxLayoutBottom;
    delete hBoxLayoutShow;
    delete vBoxLayout;

    qDebug("destruct manageStudentInfo\n");
}

void manageStudentInfo::on_btnOk_clicked()
{
    QString queryMode= comboxQueryMode->currentText();
    QString tableItem;
    if("student id" == queryMode) tableItem= "id like ";
    else if("student name" == queryMode) tableItem= "name like ";
    else if("majorCode" == queryMode) tableItem= "majorCode like ";
    else if("classCode" == queryMode) tableItem= "classCode like ";
    QString queryDetail= lineEditQueryDetail->text();
    QString queryString= tableItem + "'%"+ queryDetail + "%'";
    qDebug() << queryString;
    sqlTableMode.setFilter(queryString);
}
void manageStudentInfo::on_btnDelete_clicked()
{
    sqlTableMode.database().transaction();  /* begin a transaction*/

    QItemSelectionModel *selections = tableView.selectionModel();
    QModelIndexList selecteds = selections->selectedIndexes();
    foreach (QModelIndex index, selecteds)
    {
        int curRow = index.row();
        sqlTableMode.removeRow(curRow);
    }

    int ok = QMessageBox::warning(this,"delete!","delete the selected row?",QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes)
    {
        if(sqlTableMode.submitAll())
        {
            sqlTableMode.database().commit();
        }
        else
        {
            sqlTableMode.database().rollback();
            QMessageBox::warning(this,"warning","data change failed!");
        }
    }
    else
    {
        sqlTableMode.revertAll();
    }
}
void manageStudentInfo::on_btnCommitChange_clicked()
{
    sqlTableMode.database().transaction();
    if(sqlTableMode.submitAll())
    {
        sqlTableMode.database().commit();
    }
    else
    {
        sqlTableMode.database().rollback();
        sqlTableMode.revertAll();
        QMessageBox::warning(this,"warning","data change failed!");
    }
}
