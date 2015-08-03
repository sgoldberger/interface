#ifndef WINDOW2_H
#define WINDOW2_H

#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QDesktopWidget>
#include <QLabel>
#include <QApplication>

#include "igtlOSUtil.h"
#include "igtlClientSocket.h"
#include "igtlTransformMessage.h"
#include "igtlPointMessage.h"
#include "igtlStatusMessage.h"

//#include "global.h"

class window2: public QWidget

{
    Q_OBJECT
public:
    window2(QWidget *parent = 0);
private:
    QDesktopWidget* desktop;
    QPushButton* back;
    QPushButton* target1;
    QPushButton* target2;
    QPushButton* target3;
    QPushButton* target4;
    QPushButton* target5;
    QPushButton* target6;
    QPushButton* target7;
    QPushButton* target8;
    QLabel* title;
    QSignalMapper* sigMapper;
    QSignalMapper* sigMapper2;
    igtl::ClientSocket::Pointer socket;
   igtl::StatusMessage::Pointer statMsg;
    int numTar;
    void buildTargets(int num);
    const char* msg;
    const char* targetMsg;
    const char* depth;
private slots:
    void targetSel(int num);
    void recTar(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg, int numTar);
    void refresh();
signals:
    void moveToWindow1();
    void moveToWindow3();
    //void setTargetNum(int num);
    void setTargetNum(int num, const char* depth);
    void sendSocket(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg);
};

#endif // WINDOW2_H
