#include "login.h"

#include <QDebug>


Login::Login()
{  
    //初始化窗口插件
    logoLabel = new QLabel(this);
    IPLabel = new QLabel(this);
    portLabel = new QLabel(this);
    IPLineEdit = new QLineEdit(this);
    portLineEdit = new QLineEdit(this);
    loginBtn = new QPushButton(this);
    exitBtn = new QPushButton(this);
    //设置文本
    logoLabel->setText("飞鸽传书");
    IPLabel->setText("IP地址:");
    portLabel->setText("端口号:");
    loginBtn->setText("登陆");
    exitBtn->setText("退出");
    //设置logo文本对齐方式（居中）
    logoLabel->setAlignment(Qt::AlignHCenter);

    //栅格布局管理器
    //定义栅格布局管理器
    QGridLayout *loginLayout = new QGridLayout;
    //添加插件
    loginLayout->addWidget(logoLabel,0,1);
    loginLayout->addWidget(IPLabel,2,0);
    loginLayout->addWidget(IPLineEdit,2,1);
    loginLayout->addWidget(portLabel,4,0);
    loginLayout->addWidget(portLineEdit,4,1);
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

    //PART05版本添加  用于测试代码
    IPLineEdit->setText(QString("192.168.3.70"));
    portLineEdit->setText(QString("5005"));

}

void Login::login()
{
    //全局变量赋值
    ip = this->IPLineEdit->text();
    port = this->portLineEdit->text().toInt();

    this->hide();//隐藏对话框
    emit Upload();//发射信号
    qDebug()<<ip<<","<<port;
}
