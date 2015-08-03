#ifndef WINDOW1_H
#define WINDOW1_H

#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QDesktopWidget>
#include <QApplication>

#include "igtlOSUtil.h"
#include "igtlClientSocket.h"
#include "igtlStringMessage.h"
#include "igtlStatusMessage.h"

//#include "global.h"
class window1: public QWidget
{
    Q_OBJECT
public:
    window1(QWidget *parent = 0);
     //igtl::StatusMessage::Pointer getStatMsg();
   igtl::StatusMessage::Pointer statMsg;
signals:
    void moveToWaitWindow();
    void socketCreated(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer status);
    void refresh();
private slots:
    //void getIp();
    //void getPort();
    void connectToServer();
    void disconnectServer();
private:
    QPushButton* connectButton;
    QPushButton* disconnectButton;
    QLineEdit* ipAdd;
    QLineEdit* port;
    //QDesktopWidget* desktop;
    const QRect screenSize;
    int portNum;
    char* hostname;
    igtl::ClientSocket::Pointer socket;
    //igtl::StatusMessage::Pointer statMsg;
    igtl::TimeStamp::Pointer ts;
    int handshake();
};

#endif // WINDOW1_H
