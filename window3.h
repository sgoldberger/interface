#ifndef WINDOW3_H
#define WINDOW3_H

#include <QWidget>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QLabel>
#include <QPalette>

#include "igtlOSUtil.h"
#include "igtlStatusMessage.h"
#include "igtlClientSocket.h"

//#include "global.h"

class window3: public QWidget
{
    Q_OBJECT
public:
    window3(QWidget *parent = 0);
private:
    QDesktopWidget* desktop;
    QPushButton* back;
    QPushButton* message;
    QPushButton* send;
    QPushButton* move;
    QPushButton* cancel;
    QFont* font1;
    QFont* font2;
    int targetNum;
    int targetDepth;
    //igtl::StringMessage::Pointer strMsg;
    igtl::TimeStamp::Pointer ts;
    igtl::ClientSocket::Pointer socket;
   igtl::StatusMessage::Pointer statMsg;
    char* msg;
    QLabel* title;
    QLabel* depth;
    QLabel* tarCancel;
private slots:
    //void getTargetNum(int num);
    void getTargetNum(int num, const char* depthVal);
    void recSocket(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg);
   // void sendMsg();
    void targetSent();
    void cancelled();
    void moveSent();
    void reset();
signals:
    void moveToWindow2();
};

#endif // WINDOW3_H
