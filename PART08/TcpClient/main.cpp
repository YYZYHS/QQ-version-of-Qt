#include "chatwidget.h"
#include "login.h"
#include "registered.h"

#include <QApplication>
#include <QTextCodec>


QString ip;
int port;
QString UsrName;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ChatWidget w;
    w.show();
    return a.exec();
}
