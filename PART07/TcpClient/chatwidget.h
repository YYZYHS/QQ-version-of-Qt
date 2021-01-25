#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QFontComboBox>
#include <QComboBox>
#include <QToolButton>
#include <QTextEdit>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QFile>

//PART06_3
#include <QByteArray>

//PART04改版添加
#include "login.h"
#include "registered.h"

//PART05最简单客户端功能添加
#include <QtNetwork>
#include <QAbstractSocket>
class QTcpSocket;



class QTextBrowser;
class QFontComboBox;
class QComboBox;
class QToolButton;
class QTextEdit;
class QTableWidget;
class QLineEdit;
class QPushButton;
class QLabel;

class Login;
class Registered;

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
    //合并char
    char *stringCatenate(char *dest_str, char *src_str);

    QTcpSocket *socket;
private:
    QTextBrowser *messageBroswer;//信息文字浏览器
    QFontComboBox *fontComboBox;//字体组合框
    QComboBox *sizeCombox;//字体大小组合框
    QToolButton *boldTolBtn;//加粗按钮
    QToolButton *italicToolBtn;//倾斜按钮
    QToolButton *underlineToolBtn;//下划线按钮
    QToolButton *colorToolBtn;//更改字体颜色按钮
    QToolButton *sendToolBtn;//传输文件按钮
    QToolButton *saveToolBtn;//保存聊天记录按钮
    QToolButton *clearToolBtn;//清空聊天记录按钮
    QTextEdit *messageTextEdit;//消息输入框
    QTableWidget *userTableWidget;//用户列表
    QPushButton *sendBtn;//发送按钮
    QLabel *usrNumlabel;//在线用户数
    QPushButton *exitBtn;//退出按钮
    QPushButton *refreshBtn;//刷新按钮
    QLineEdit *chooseusrNumber;//选择用户编号

    //PART04改版添加
    QPushButton *loginBtn;//登陆弹窗按钮
    QPushButton *regBtn;//注册弹窗按钮





private slots:
    void setIP();
    void setusrname();
    void upload();

    //PART06_1
    void receiveMessage();//接收信息
    void sendMessage();

};
#endif // CHATWIDGET_H
