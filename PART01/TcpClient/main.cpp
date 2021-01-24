#include "chatwidget.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWidget w;
    Login l;
    if(l.exec() == QDialog::Accepted)
    w.show();
    return a.exec();
}
