#include "chatwidget.h"

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

    //设置窗口属性

}

ChatWidget::~ChatWidget()
{
}

