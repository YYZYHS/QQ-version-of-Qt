#include "chatwidget.h"
#include <QDebug>
#include <string.h>

bool boldBtn = 1;
bool italBtn = 1;
bool underBtn = 1;


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

    connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(setIP()));
    connect(regBtn,SIGNAL(clicked(bool)),this,SLOT(setusrname()));
    connect(sendBtn,SIGNAL(clicked(bool)),this,SLOT(sendMessage()));

    /*PART07*/

    connect(fontComboBox,SIGNAL(currentFontChanged(const QFont)),this,SLOT(fontComboBoxcurrentFontChanged(const QFont)));
    connect(sizeCombox,SIGNAL(currentIndexChanged(const QString)),this,SLOT(sizeComboBox_currentIndexChanged(const QString)));
    connect(boldTolBtn,SIGNAL(clicked(bool)),this,SLOT(boldToolBtn_clicked()));
    connect(italicToolBtn,SIGNAL(clicked(bool)),this,SLOT(italicToolBtn_clicked()));
    connect(underlineToolBtn,SIGNAL(clicked(bool)),this,SLOT(underlineToolBtn_clicked()));
    connect(colorToolBtn,SIGNAL(clicked(bool)),this,SLOT(colorToolBtn_clicked()));
    connect(saveToolBtn,SIGNAL(clicked(bool)),this,SLOT(saveToolBtn_clicked()));
    connect(clearToolBtn,SIGNAL(clicked(bool)),this,SLOT(clearToolBtn_clicked()));
    connect(exitBtn,SIGNAL(clicked(bool)),this,SLOT(exitButton_clicked()));
    connect(messageTextEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
                this, SLOT(currentFormatChanged(const QTextCharFormat)));

    /*part08*/
    connect(refreshBtn,SIGNAL(clicked()),this,SLOT(F5()));

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
    connect(&b,SIGNAL(sendusr()),this,SLOT(sendusrname()));
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
    //QString str = arr.data();//转换
    //char buffer[1024];
    char *a = arr.data();
//    if(a[0] == 0)
//    a[0] == '1';
    switch (a[0])
    {
    case '0'://0 ---- 发送消息
    {
        qDebug()<<"case 0";
        receivemessage(arr);
        break;
    }
    case '1'://1 ---- 发送文件
    {
        receivefile(a);
        break;
    }
    case '2'://2 ---- 请求刷新在线用户列表
    {
        receivelist(a);
        break;
    }

    }

}

void ChatWidget::sendMessage()
{
    //发送信息

    //PART07_1
    //按照开头的第一个字节确定需要选择的信息发送方式




    if(messageTextEdit->toPlainText() == "")
    {
        QMessageBox::warning(0,tr("警告"),
                             tr("发送内容不能为空"),QMessageBox::Ok);
        return;
    }

    QString aim = chooseusrNumber->text();
    QString str = messageTextEdit->toPlainText();
    QString data;
    QTextStream out(&data,QIODevice::WriteOnly);
    out<<0<<aim<<str<<'\0';
    socket->write(data.toUtf8().data(),strlen(data.toUtf8().data()));
}

// 更改字体族
void ChatWidget::fontComboBoxcurrentFontChanged(const QFont &f)
{
    qDebug()<<"123";
    this->messageTextEdit->setCurrentFont(f);
    this->messageTextEdit->setFocus();
}
// 更改字体大小
void ChatWidget::sizeComboBox_currentIndexChanged(const QString &arg1)
{
    this->messageTextEdit->setFontPointSize(arg1.toDouble());
    this->messageTextEdit->setFocus();
}
// 加粗
void ChatWidget::boldToolBtn_clicked()
{
    qDebug()<<"321";
    if(boldBtn)//boldBtn == 1
    {
        this->messageTextEdit->setFontWeight(QFont::Bold);
        boldBtn = 0;
    }

        else
    {
        this->messageTextEdit->setFontWeight(QFont::Normal);
        boldBtn = 1;
    }
        this->messageTextEdit->setFocus();
}
// 倾斜
void ChatWidget::italicToolBtn_clicked()
{
    this->messageTextEdit->setFontItalic(italBtn);
    if(italBtn)
    {
        italBtn = 0;
    }
    else
    {
        italBtn = 1;
    }
    this->messageTextEdit->setFocus();
}
// 下划线
void ChatWidget::underlineToolBtn_clicked()
{
    this->messageTextEdit->setFontUnderline(underBtn);
    if(underBtn)
    {
        underBtn = 0;
    }
    else
    {
        underBtn = 1;
    }
    this->messageTextEdit->setFocus();
}
// 字体颜色
void ChatWidget::colorToolBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
        if (color.isValid())
        {
            this->messageTextEdit->setTextColor(color);
            this->messageTextEdit->setFocus();
        }
}
// 更改按钮状态
void ChatWidget::currentFormatChanged(const QTextCharFormat &format)
{
    fontComboBox->setCurrentFont(format.font());
    // 如果字体大小出错(因为我们最小的字体为9)，使用12
    if (format.fontPointSize() < 9)
    {
        this->sizeCombox->setCurrentIndex(3);
    }
    else
    {
        this->sizeCombox->setCurrentIndex(this->sizeCombox
                                    ->findText(QString::number(format.fontPointSize())));
    }
    this->boldTolBtn->setChecked(format.font().bold());
    this->italicToolBtn->setChecked(format.font().italic());
    this->underlineToolBtn->setChecked(format.font().underline());
    this->color = format.foreground().color();
}
// 保存聊天记录
void ChatWidget::saveToolBtn_clicked()
{
    if(this->messageBroswer->document()->isEmpty())
    {
        QMessageBox::warning(0, tr("警告"), tr("聊天记录为空，无法保存！"), QMessageBox::Ok);
    }
    else
    {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("保存聊天记录"), tr("聊天记录"), tr("文本(*.txt);;All File(*.*)"));
        if(!fileName.isEmpty())
            saveFile(fileName);
    }

}
// 清空聊天记录
void ChatWidget::clearToolBtn_clicked()
{
    this->messageBroswer->clear();
}
// 退出按钮
void ChatWidget::exitButton_clicked()
{
    QString data;
    QTextStream out(&data,QIODevice::WriteOnly);
    out<<4<<'\0';
    socket->write(data.toUtf8().data(),strlen(data.toUtf8().data()));
    close();
}
// 保存文件
bool ChatWidget::saveFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("保存文件"),
                             tr("无法保存文件 %1:\n %2").arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << this->messageBroswer->toPlainText();

    return true;
}

void ChatWidget::sendusrname()
{
    //发送信息

        //PART07_1
        //按照开头的第一个字节确定需要选择的信息发送方式
        //0 ---- 发送消息
        //1 ---- 发送文件
        //2 ---- 请求刷新在线用户列表
        //3 ---- 注册用户
        QString data;
        QTextStream out(&data,QIODevice::WriteOnly);
        out<<3<<UsrName<<'\0';
        socket->write(data.toUtf8().data(),strlen(data.toUtf8().data()));
}

void ChatWidget::F5()
{
    QString data;
    QTextStream out(&data,QIODevice::WriteOnly);
    out<<2<<'\0';
    socket->write(data.toUtf8().data(),strlen(data.toUtf8().data()));
}

void ChatWidget::receivemessage(QByteArray ba)
{
    qDebug()<<"receivemessage";
    QString str = ba.data();
    messageBroswer->setText(str);

//    char  *msg = ba.data();
//    char buff[1026];
//    char number;
//    number = buff[0];

//    char *msg;
//    QString Msg;
//    QTextStream in(&Msg,QIODevice::WriteOnly);
//    char *buff = ba.data();
//    memcpy(msg,buff+2,sizeof(ba.data()));
//    in<<msg<<'\n';
//    messageBroswer->setText(Msg.toUtf8().data());;


}

void ChatWidget::receivefile(char *)
{

}

void ChatWidget::receivelist(char *)
{

}

