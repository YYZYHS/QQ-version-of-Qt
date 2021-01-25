#include "chatwidget.h"
#include "login.h"
#include "registered.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWidget w;
    Login l;
    Registered r;
    if(l.exec() == QDialog::Accepted)
    {
        if(r.exec() == QDialog::Accepted)
        {
            w.show();
        }
    }

    return a.exec();
}
