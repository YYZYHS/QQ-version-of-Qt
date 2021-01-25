#include "registered.h"
#include <QDebug>

Registered::Registered()
{
    //定义
    setWindowTitle("注册用户");
    registered = new QPushButton(this);
    usrname = new QLineEdit(this);
    //文本
    registered->setText(QString("注册"));
    usrname->setPlaceholderText(QString("请输入用户名"));

    //垂直布局
    QVBoxLayout *horizontalLayout_1 = new QVBoxLayout;
    horizontalLayout_1->addWidget(usrname);
    horizontalLayout_1->addWidget(registered);
    setLayout(horizontalLayout_1);

    //信号与槽
    connect(registered,SIGNAL(clicked(bool)),this,SLOT(Register()));
}

void Registered::Register()
{
    qDebug()<<"0";
    if(1)
    {
        qDebug()<<"1";
        accept();
        qDebug()<<"2";
    }
    else
    {
        QMessageBox::warning(this,"警告！","用户名或密码错误！",QMessageBox::Yes);
//        IPLineEdit->clear();
//        portLabel->clear();
//        IPLineEdit->setFocus();
    }
}
