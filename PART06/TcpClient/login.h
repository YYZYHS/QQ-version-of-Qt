#ifndef LOGIN_H
#define LOGIN_H

//需要包含的类
#include <QWidget>      //窗口类
#include <QDialog>      //对话框类
#include <QLabel>       //标签类
#include <QPushButton>  //按钮类
#include <QLineEdit>    //输入行类
#include <QMessageBox>  //消息类
#include <QGridLayout>  //栅格布局管理器类
#include <QString>

//全局变量
extern QString ip;
extern int port;

//类的前置声明
class QLabel;
class QLineEdit;
class QPushButton;

class Login : public QDialog
{
    Q_OBJECT
public:
    Login();
    //~Login();

private:
    QLabel *IPLabel;           //文本：IP地址
    QLabel *portLabel;           //文本：端口号
    QLabel *logoLabel;          //文本：logo
    QPushButton *loginBtn;      //按钮：登陆
    QPushButton *exitBtn;       //按钮：退出
    QLineEdit *IPLineEdit;     //输入框：IP地址
    QLineEdit *portLineEdit;     //输入框：端口号
private slots:
    void login();               //登陆进聊天室界面


signals:
    void Upload();//登录的信号

};

#endif // LOGIN_H
