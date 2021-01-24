#include "login.h"

Login::Login()
{
    setMinimumSize(400,150);
    setMaximumSize(400,150);
    logoLabel = new QLabel(this);
    usrLabel = new QLabel(this);
    pwdLabel = new QLabel(this);
    logup = new QLabel(this);
    pswfind = new QLabel(this);
    usrLineEdit = new QLineEdit(this);
    pwdLineEdit = new QLineEdit(this);
    loginBtn = new QPushButton(this);
    exitBtn = new QPushButton(this);

    logoLabel->setText("飞鸽传书");
    usrLabel->setText("用户名:");
    pwdLabel->setText("密码:");
    logup->setText("注册账户");
    pswfind->setText("找回密码");
    loginBtn->setText("登陆");
    exitBtn->setText("退出");

    logoLabel->setAlignment(Qt::AlignHCenter);

    QGridLayout *loginLayout = new QGridLayout;
    loginLayout->addWidget(logoLabel,0,1);
    loginLayout->addWidget(usrLabel,2,0);
    loginLayout->addWidget(usrLineEdit,2,1);
    loginLayout->addWidget(logup,2,2);
    loginLayout->addWidget(pwdLabel,4,0);
    loginLayout->addWidget(pwdLineEdit,4,1);
    loginLayout->addWidget(pswfind,4,2);
    loginLayout->addWidget(loginBtn,6,0);
    loginLayout->addWidget(exitBtn,6,2);


    loginLayout->setHorizontalSpacing(10);
    loginLayout->setVerticalSpacing(10);
    loginLayout->setContentsMargins(10,10,10,10);

    connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(login()));
    connect(exitBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    setLayout(loginLayout);
    setWindowTitle("飞鸽传书    登陆");
    setWindowIcon(QIcon(":/Image/Image/217c8d364111f8013a8afe7fc51fe572.png"));


}

void Login::login()
{
//    if(usrLineEdit->text().trimmed() == "yyz"
//            && pwdLineEdit->text().trimmed() == "123456")
    if(1)
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,"警告！","用户名或密码错误！",QMessageBox::Yes);
        usrLineEdit->clear();
        pwdLabel->clear();
        usrLineEdit->setFocus();
    }
}
