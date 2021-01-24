#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QGridLayout>

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
    QLabel *usrLabel;
    QLabel *pwdLabel;
    QLabel *logoLabel;
    QLabel *logup;
    QLabel *pswfind;
    QLineEdit *usrLineEdit;
    QLineEdit *pwdLineEdit;
    QPushButton *loginBtn;
    QPushButton *exitBtn;
private slots:
    void login();

};

#endif // LOGIN_H
