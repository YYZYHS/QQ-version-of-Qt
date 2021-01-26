#ifndef REGISTERED_H
#define REGISTERED_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QVBoxLayout>
#include <QMessageBox>

extern QString UsrName;

class QPushButton;
class QLineEdit;
class QVBoxLayout;

class Registered : public QDialog
{
    Q_OBJECT
public:
    Registered();
private:
    QLineEdit *usrname;//注册用户名输入框
    QPushButton *registered;//注册按钮
private slots:
    void Register();
signals:
    void sendusr();


};

#endif // REGISTERED_H
