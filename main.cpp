#include <QApplication>
#include "window1.h"
#include "window2.h"
#include "window3.h"
#include "waitwindow.h"

//extern igtl::StatusMessage::Pointer statusMsg;

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

   window1 w1;
   waitWindow wait;
   window2 w2;
   window3 w3;

   QObject::connect(&w1, SIGNAL(socketCreated(igtl::ClientSocket::Pointer, igtl::StatusMessage::Pointer)), &wait, SLOT(recSocket(igtl::ClientSocket::Pointer, igtl::StatusMessage::Pointer)));
   QObject::connect(&w1, SIGNAL(refresh()), &w2, SLOT(refresh()));
   QObject::connect(&wait, SIGNAL(sendNumTar(igtl::ClientSocket::Pointer, igtl::StatusMessage::Pointer, int)), &w2, SLOT(recTar(igtl::ClientSocket::Pointer, igtl::StatusMessage::Pointer, int)));
   //QObject::connect(&wait, SIGNAL(sendNumTar(igtl::ClientSocket::Pointer, igtl::StatusMessage::Pointer, int)), &w3, SLOT(recSocket(igtl::ClientSocket::Pointer,igtl::StatusMessage::Pointer, int)));
   QObject::connect(&wait, SIGNAL(hideW1()), &w1, SLOT(hide()));
   QObject::connect(&wait, SIGNAL(backToWindow1()), &w1, SLOT(show()));
   QObject::connect(&w2, SIGNAL(sendSocket(igtl::ClientSocket::Pointer, igtl::StatusMessage::Pointer)), &w3, SLOT(recSocket(igtl::ClientSocket::Pointer, igtl::StatusMessage::Pointer)));
   QObject::connect(&w2, SIGNAL(moveToWindow1()), &w1, SLOT(show()));
   QObject::connect(&w2, SIGNAL(moveToWindow3()), &w3, SLOT(show()));
   //QObject::connect(&w2, SIGNAL(setTargetNum(int)), &w3, SLOT(getTargetNum(int)));
   QObject::connect(&w2, SIGNAL(setTargetNum(int, const char*)), &w3, SLOT(getTargetNum(int, const char*)));
   QObject::connect(&w3, SIGNAL(moveToWindow2()), &w2, SLOT(show()));

   w1.show();

    return app.exec();
}


