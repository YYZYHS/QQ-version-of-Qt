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
    QLabel *usrLabel;           //文本：账号
    QLabel *pwdLabel;           //文本：密码
    QLabel *logoLabel;          //文本：logo
    QLabel *logup;              //文本：注册账号（用以日后连接数据库使用）
    QLabel *pswfind;            //文本：找回密码（用以日后连接数据库使用）
    QLineEdit *usrLineEdit;     //输入框：账号
    QLineEdit *pwdLineEdit;     //输入框：密码
    QPushButton *loginBtn;      //按钮：登陆
    QPushButton *exitBtn;       //按钮：退出
private slots:
    void login();               //登陆进聊天室界面

};

#endif // LOGIN_H
