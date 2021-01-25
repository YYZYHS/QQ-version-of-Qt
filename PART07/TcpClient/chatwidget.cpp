#include "chatwidget.h"
#include <QDebug>
#include <string.h>


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

    //PART06_5
    connect(sendBtn,SIGNAL(clicked(bool)),this,SLOT(sendMessage()));


}

ChatWidget::~ChatWidget()
{
}

void ChatWidget::setIP()
{

    Login a;
    connect(&a,SIGNAL(Upload()),this,SLOT(upload()));
    a.exec();

}

void ChatWidget::setusrname()
{
    Registered b;
    b.exec();
}

void ChatWidget::upload()
{
    //创建socket
    //socket=IP地址+端口号
    socket = new QTcpSocket(this);
    //连接
    socket->connectToHost(ip,port);
    //PART06_2
    //接收信息
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
}

void ChatWidget::receiveMessage()
{
    //PART06_4
    QByteArray arr = socket->readAll();//读取
    QString str = arr.data();//转换
    messageBroswer->setText(str);

    //一个小功能
    if(str == "111")
    {
        this->hide();//隐藏窗口
    }
    else if(str == "222")
    {
        this->show();//显示窗口
    }
}

void ChatWidget::sendMessage()
{
    //发送信息

    //PART07_1
    //按照开头的第一个字节确定需要选择的信息发送方式
    //0 ---- 发送消息
    //1 ---- 发送文件
    //2 ---- 请求刷新在线用户列表
    //3 ---- 注册用户
qDebug()<<"1";
    if(messageTextEdit->toPlainText() == "")
    {
        QMessageBox::warning(0,tr("警告"),
                             tr("发送内容不能为空"),QMessageBox::Ok);
        return;
    }
    qDebug()<<"2";
    //消息内容
    QString str = messageTextEdit->toPlainText();
    char buf[1022];
    QByteArray ba = str.toLocal8Bit();
    memcpy(buf,ba.data(),ba.size()+1);//加1是为了最后的终结符，否则转换回来的时候不知道什么时候截止
qDebug()<<"3";
    //控制位和选择位
    char control[1024];
    char chose[1023];
qDebug()<<"4";
    control[0] = '0';
    QString str1 = chooseusrNumber->text();
    QByteArray ba1 = str1.toLocal8Bit();
    memcpy(chose,ba1.data(),ba.size()+1);
qDebug()<<"5";
    //合并
//    char *bufBefore = stringCatenate(control,chose);
//    char *buffe = stringCatenate(bufBefore,buf);
    stringCatenate(control,chose);
    stringCatenate(control,buf);
    qDebug()<<control;
    qDebug()<<control[0];
    qDebug()<<control[1];
qDebug()<<"6";
    //发送
    socket->write(control);
//    char bufBefore[1024];
//    //memset(&bufBefore,9,sizeof(bufBefore));
//    bufBefore[0] = '0';//控制位
//    QString str1 = chooseusrNumber->text();
//    QByteArray ba1 = str1.toLocal8Bit();
//    memcpy(bufBefore)
//    //bufBefore[1] = chooseusrNumber->text();//目标位

//    //合流
//    char *mesg = strcat(bufBefore,bufAfter);
//    socket->write(mesg);
//    qDebug()<<mesg;
    //socket->write(str.toUtf8());
}


char *ChatWidget::stringCatenate(char *dest_str, char *src_str)
{
    char *dtemp = NULL;
    char *stemp = NULL;
    dtemp = dest_str;
    stemp = src_str;
    while(*dtemp != '\0')
    {
        dtemp++;
    }
    while(*stemp != '\0')
    {
        *dtemp = *stemp;
        dtemp++;
        stemp++;
    }
    *dtemp = '\0';
    return dest_str;
}
