#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
};
#endif // CHATWIDGET_H
