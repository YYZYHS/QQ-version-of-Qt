﻿#ifndef CHATWIDGET_H
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
#include <QByteArray>
#include "login.h"
#include "registered.h"
#include <QtNetwork>
#include <QAbstractSocket>


/*PART07*/
#include <QDataStream>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>

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

extern bool boldBtn;
extern bool italBtn;
extern bool underBtn;

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
    QTcpSocket *socket;
    bool saveFile(const QString& fileName);
//    //合并char
//    char *stringCatenate(char *dest_str, char *src_str);


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
    QPushButton *loginBtn;//登陆弹窗按钮
    QPushButton *regBtn;//注册弹窗按钮

    /*PART07*/
    QColor color;
    QString fileName;
private slots:
    void setIP();
    void setusrname();
    void upload();
    void receiveMessage();//接收信息
    void sendMessage();
    void sendusrname();
    //各类按钮
    //更改字体族
    void fontComboBoxcurrentFontChanged(const QFont &f);
    //更改字体大小
    void sizeComboBox_currentIndexChanged(const QString &arg1);
    //加粗
    void boldToolBtn_clicked();
    //倾斜
    void italicToolBtn_clicked();
    //下划线
    void underlineToolBtn_clicked();
    //字体颜色
    void colorToolBtn_clicked();
    //输入框更新
    void currentFormatChanged(const QTextCharFormat &format);
    //保存聊天记录
    void saveToolBtn_clicked();
    //清除聊天记录
    void clearToolBtn_clicked();
    //退出
    void exitButton_clicked();
    //刷新用户列表
    void F5();

    //收信息
    void receivemessage(QByteArray);
    //收文件
    void receivefile(char *);
    //更新列表
    void receivelist(char *);

};
#endif // CHATWIDGET_H
