#ifndef WAITWINDOW_H
#define WAITWINDOW_H

#include <QWidget>
#include <QFont>
#include <QLabel>
#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>

#include "igtlOSUtil.h"
#include "igtlClientSocket.h"
#include "igtlTransformMessage.h"
#include "igtlStatusMessage.h"

//#include "global.h"

class waitWindow: public QWidget
{
    Q_OBJECT
public:
    waitWindow(QWidget* parent = 0);
private:
    QLabel* title;
    QDesktopWidget* desktop;
    int numTar;
    igtl::ClientSocket::Pointer socket;
    void recTar(igtl::ClientSocket::Pointer sckt);
    QPushButton* cancel;
    bool noTargets;
   igtl::StatusMessage::Pointer statMsg;
   const char* sNumTar;
private slots:
    void recSocket(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer statMsg);
    void cancelled();
signals:
    void sendNumTar(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg, int numTar);
    void backToWindow1();
    void hideW1();
};

#endif // WAITWINDOW_H
