#include "chatwidget.h"
#include <QDebug>


ChatWidget::ChatWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800,450);
    setMaximumSize(800,450);
    setWindowTitle("飞鸽传书聊天工具");

    //定义窗口插件
    messageBroswer = new QTextBrowser(this);//信息文字浏览器
    fontComboBox = new QFontComboBox(this);//字体组合框
    sizeCombox = new QComboBox(this);//字体大小组合框
    boldTolBtn = new QToolButton(this);//加粗按钮
    italicToolBtn = new QToolButton(this);//倾斜按钮
    underlineToolBtn = new QToolButton(this);//下划线按钮
    colorToolBtn = new QToolButton(this);//更改字体颜色按钮
    sendToolBtn = new QToolButton(this);//传输文件按钮
    saveToolBtn = new QToolButton(this);//保存聊天记录按钮
    clearToolBtn = new QToolButton(this);//清空聊天记录按钮
    messageTextEdit = new QTextEdit(this);//消息输入框
    userTableWidget = new QTableWidget(this);//用户列表
    sendBtn = new QPushButton(this);//发送按钮
    usrNumlabel = new QLabel(this);//在线用户数
    exitBtn = new QPushButton(this);//退出按钮
    chooseusrNumber = new QLineEdit(this);//选择用户编号   
    refreshBtn = new QPushButton(this);//刷新

//    chooseusrNumber->text();

    ///////////////////设置窗口属性//////////////////////

    //字体大小组合框
    //添加下拉选项  9-22
    for(int i =9;i <= 22;i++)
    {
        sizeCombox->addItem(QString::number(i));
    }
    //设置指定索引号显示
    sizeCombox->setCurrentIndex(3);

    //各种ToolButton属性修改
    //按钮大小
    boldTolBtn->setFixedSize(30,30);
    italicToolBtn->setFixedSize(30,30);
    underlineToolBtn->setFixedSize(30,30);
    colorToolBtn->setFixedSize(30,30);
    sendToolBtn->setFixedSize(30,30);
    saveToolBtn->setFixedSize(30,30);
    clearToolBtn->setFixedSize(30,30);
    //按钮图标大小
    boldTolBtn->setIconSize(QSize(22,22));
    italicToolBtn->setIconSize(QSize(22,22));
    underlineToolBtn->setIconSize(QSize(22,22));
    colorToolBtn->setIconSize(QSize(22,22));
    sendToolBtn->setIconSize(QSize(22,22));
    saveToolBtn->setIconSize(QSize(22,22));
    clearToolBtn->setIconSize(QSize(22,22));
    //按钮设置自动浮起
    boldTolBtn->setAutoRaise(true);
    italicToolBtn->setAutoRaise(true);
    underlineToolBtn->setAutoRaise(true);
    colorToolBtn->setAutoRaise(true);
    sendToolBtn->setAutoRaise(true);
    saveToolBtn->setAutoRaise(true);
    clearToolBtn->setAutoRaise(true);
    //按钮设置点击后按下
    boldTolBtn->setChecked(true);
    italicToolBtn->setChecked(true);
    underlineToolBtn->setChecked(true);
    //设置按钮文本
    boldTolBtn->setToolTip("加粗");
    italicToolBtn->setToolTip("倾斜");
    underlineToolBtn->setToolTip("下划线");
    colorToolBtn->setToolTip("更改字体颜色");
    sendToolBtn->setToolTip("传输文件");
    saveToolBtn->setToolTip("保存聊天记录");
    clearToolBtn->setToolTip("清空聊天记录");
    //设置按钮图标
    boldTolBtn->setIcon(QIcon(":/Image/Image/bold.png"));
    italicToolBtn->setIcon(QIcon(":/Image/Image/italic.png"));
    underlineToolBtn->setIcon(QIcon(":/Image/Image/under.png"));
    colorToolBtn->setIcon(QIcon(":/Image/Image/color.png"));
    sendToolBtn->setIcon(QIcon(":/Image/Image/send.png"));
    saveToolBtn->setIcon(QIcon(":/Image/Image/save.png"));
    clearToolBtn->setIcon(QIcon(":/Image/Image/clear.png"));

    //设置表格空间QTableWidget的属性
    //设置表格空间单选
    userTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置一次选中一行
    userTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置不显示表格线
    userTableWidget->setShowGrid(false);
    //设置列数+列宽
    userTableWidget->setColumnCount(2);
    //setSectionResizeMode
    userTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    userTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置表头
    QStringList strs;
    strs << QStringLiteral("编号") << QStringLiteral("用户名");
    userTableWidget->setHorizontalHeaderLabels(strs);

    //设置各种普通按钮属性
    sendBtn->setText(QString("发送"));
    exitBtn->setText(QString("退出"));
    refreshBtn->setText("刷新列表");

    //设置标签类属性
    usrNumlabel->setText(QString("在线人数："));

    //选择框
    chooseusrNumber->setMinimumWidth(200);
    chooseusrNumber->setMaximumWidth(200);
    chooseusrNumber->setPlaceholderText(QString("请输入要发送的用户编号"));

    //////////////////////////////布局管理///////////////////////


    //PART4大改版添加
    loginBtn = new QPushButton(this);//登陆
    regBtn = new QPushButton(this);//注册

    loginBtn->setText(QString("设置服务器IP和端口号"));
    regBtn->setText(QString("设置客户端用户名"));

    QHBoxLayout *horizontalLayout_6 = new QHBoxLayout;
    horizontalLayout_6->addWidget(loginBtn);
    horizontalLayout_6->addWidget(regBtn);

    setWindowIcon(QIcon(":/Image/Image/217c8d364111f8013a8afe7fc51fe572.png"));



    //窗口一：各种ToolButton+字体组合框  水平布局
    QHBoxLayout *horizontalLayout_1 = new QHBoxLayout;
    horizontalLayout_1->addWidget(fontComboBox);
    horizontalLayout_1->addWidget(sizeCombox);
    horizontalLayout_1->addWidget(boldTolBtn);
    horizontalLayout_1->addWidget(italicToolBtn);
    horizontalLayout_1->addWidget(underlineToolBtn);
    horizontalLayout_1->addWidget(colorToolBtn);
    horizontalLayout_1->addWidget(sendToolBtn);
    horizontalLayout_1->addWidget(saveToolBtn);
    horizontalLayout_1->addWidget(clearToolBtn);

    //窗口二：信息文字浏览器+窗口一+消息输入框  垂直布局
    QVBoxLayout *horizontalLayout_2 = new QVBoxLayout;
    horizontalLayout_2->addWidget(messageBroswer);
    //PART04新增加内容
    horizontalLayout_2->addLayout(horizontalLayout_6);
    horizontalLayout_2->addLayout(horizontalLayout_1);
    horizontalLayout_2->addWidget(messageTextEdit);

    //窗口三：窗口二+用户列表  水平布局
    QHBoxLayout *horizontalLayout_3 = new QHBoxLayout;
    horizontalLayout_3->addLayout(horizontalLayout_2);
    horizontalLayout_3->addWidget(userTableWidget);

    //窗口四：选择用户编号框+发送按钮+在线用户数+退出按钮+刷新按钮 水平布局
    QHBoxLayout *horizontalLayout_4 = new QHBoxLayout;
    horizontalLayout_4->addWidget(chooseusrNumber);
    horizontalLayout_4->addWidget(sendBtn);
    horizontalLayout_4->addWidget(usrNumlabel);
    horizontalLayout_4->addWidget(refreshBtn);
    horizontalLayout_4->addWidget(exitBtn);


    //窗口五：窗口三+窗口四  垂直布局
    QVBoxLayout *horizontalLayout_5 = new QVBoxLayout;
    horizontalLayout_5->addLayout(horizontalLayout_3);
    horizontalLayout_5->addLayout(horizontalLayout_4);

    //加入主窗口
    setLayout(horizontalLayout_5);

    //PART04大改版添加
    connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(setIP()));
    connect(regBtn,SIGNAL(clicked(bool)),this,SLOT(setusrname()));


}

ChatWidget::~ChatWidget()
{
}

void ChatWidget::setIP()
{
    //PART05版本添加
    Login a;
    connect(&a,SIGNAL(Upload()),this,SLOT(upload()));
    a.exec();

}

void ChatWidget::setusrname()
{
    Registered b;
    b.exec();
}

//PART05版本添加
void ChatWidget::upload()
{
    //创建socket
    //socket=IP地址+端口号
    socket = new QTcpSocket(this);
    //连接
    socket->connectToHost(ip,port);
}
