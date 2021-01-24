#include "login.h"

Login::Login()
{  
    //初始化窗口插件
    logoLabel = new QLabel(this);
    usrLabel = new QLabel(this);
    pwdLabel = new QLabel(this);
    logup = new QLabel(this);
    pswfind = new QLabel(this);
    usrLineEdit = new QLineEdit(this);
    pwdLineEdit = new QLineEdit(this);
    loginBtn = new QPushButton(this);
    exitBtn = new QPushButton(this);
    //设置文本
    logoLabel->setText("飞鸽传书");
    usrLabel->setText("用户名:");
    pwdLabel->setText("密码:");
    logup->setText("注册账户");
    pswfind->setText("找回密码");
    loginBtn->setText("登陆");
    exitBtn->setText("退出");
    //设置logo文本对齐方式（居中）
    logoLabel->setAlignment(Qt::AlignHCenter);

    //栅格布局管理器
    //定义栅格布局管理器
    QGridLayout *loginLayout = new QGridLayout;
    //添加插件
    loginLayout->addWidget(logoLabel,0,1);
    loginLayout->addWidget(usrLabel,2,0);
    loginLayout->addWidget(usrLineEdit,2,1);
    loginLayout->addWidget(logup,2,2);
    loginLayout->addWidget(pwdLabel,4,0);
    loginLayout->addWidget(pwdLineEdit,4,1);
    loginLayout->addWidget(pswfind,4,2);
    loginLayout->addWidget(loginBtn,6,0);
    loginLayout->addWidget(exitBtn,6,2);
    //设置管理器间距
    loginLayout->setHorizontalSpacing(10);//两列之间的间距
    loginLayout->setVerticalSpacing(10);//两行之间的间距
    loginLayout->setContentsMargins(10,10,10,10);//设置左侧、顶部、右侧和底部边距
    //设置窗口大小
    setMinimumSize(400,150);//窗口最大大小
    setMaximumSize(400,150);//窗口最小大小
    //安装布局管理器
    setLayout(loginLayout);

    //设置窗口名和窗口图标
    setWindowTitle("飞鸽传书    登陆");
    setWindowIcon(QIcon(":/Image/Image/217c8d364111f8013a8afe7fc51fe572.png"));

    //设置信号与槽
    connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(login()));
    connect(exitBtn,SIGNAL(clicked(bool)),this,SLOT(close()));



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
