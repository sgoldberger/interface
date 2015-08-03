#include "window1.h"
#include <QDebug>

window1::window1(QWidget *parent):
    QWidget(parent)
{
    //set window
    //const QRect screenSize = desktop->screenGeometry();
    int screenW = 800;
    int screenH = 600;
    setGeometry(0,0,800,600);
    QPalette pal = this -> palette();
    pal.setColor(QPalette::Window, Qt::black);
    this->setPalette(pal);

    QFont font("", .04 *screenH, 25, false);
    font.setFamily(font.defaultFamily());


    //build input lines
/*
    ipAdd = new QLineEdit(this);
    ipAdd -> setGeometry(.25 * screenW, .05 * screenH, .5 * screenW, .125 * screenH);
    ipAdd -> setPlaceholderText("Enter IP Address");
    ipAdd -> setFont (font);

    port = new QLineEdit(this);
    port -> setGeometry(.25*screenW, .2 * screenH, .5 * screenW,.125 * screenH);
    port -> setPlaceholderText("Enter Port Number");
    port -> setFont(font);

*/
    //build buttons
    connectButton = new QPushButton("Connect to server", this);
    connectButton -> setGeometry(.25 * screenW, .2* screenH, .5 * screenW, .3 * screenH);
    connectButton -> setFont(font);
    //connectButton -> setEnabled(false);

    disconnectButton = new QPushButton("Disconnect", this);
    disconnectButton -> setGeometry(.25 * screenW, .5 * screenH, .5 * screenW, .125 * screenH);
    disconnectButton -> setFont(font);
    disconnectButton -> setEnabled(false);

    //connect(connectButton, SIGNAL(clicked()), this, SLOT(hide()));
   // connect(ipAdd, SIGNAL(editingFinished()), this, SLOT(getIp()));
   //connect(port, SIGNAL (editingFinished()), this, SLOT(getPort()));
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(disconnectButton, SIGNAL(clicked()), this, SLOT(disconnectServer()));
}

/*
void window1::getIp()
{
    QString input = ipAdd->text();
    QByteArray ba = input.toLocal8Bit();
    hostname = new char[20];
    std::strcpy(hostname, ba.data());
}

void window1::getPort()
{
    QString input = port->text();
    //portNum = new int;
    //*portNum = input.toInt();
    connectButton ->setEnabled(true);
}

*/
void window1::connectToServer()
{
   //Establish Connection
   char* hostname = "localhost" ;
   int portNum = 18944;
   socket = igtl::ClientSocket::New();
   int r = socket->ConnectToServer(hostname, portNum);

   if (r != 0)
   {
      connectButton -> setText("No connection - Try Again");
   }

   else
   {
      socket -> SetReceiveTimeout(250);
      if (handshake())
      {
          qDebug()<<"socket1: " << socket;
          qDebug()<<"statMsg1: " <<statMsg;
      emit socketCreated(socket, statMsg); //move to wait window

      connectButton -> setText("Connected");
      connectButton -> setEnabled(false);
      disconnectButton -> setEnabled(true);
      disconnectButton -> setText("Disconnect");
      }

      else
      {
          connectButton -> setText("Incorrect server - Try Again");
      }
    }
}

void window1::disconnectServer()
{
    socket->CloseSocket();

    disconnectButton -> setText("Disconnected");
    disconnectButton -> setEnabled(false);

    connectButton -> setEnabled(true);
    connectButton -> setText("Connect");

    emit refresh();
}

int window1::handshake()
{
    //send handshake
    statMsg = igtl::StatusMessage::New();
    statMsg->SetDeviceName("Interface");

    statMsg -> SetCode(1);
    statMsg -> SetStatusString("TouchscreenHandshake");
    statMsg->Pack();
    socket->Send(statMsg->GetPackPointer(), statMsg->GetPackSize());
    
    //receive handshake
    igtl::MessageHeader::Pointer headerMsg;
    headerMsg = igtl::MessageHeader::New();

    headerMsg->InitPack();
    int r = socket->Receive(headerMsg -> GetPackPointer(), headerMsg->GetPackSize());
    if (r == 0)
    {
       socket->CloseSocket();
       exit(0);
    }
    if (r != headerMsg->GetPackSize())
    {
       return 0;
    }

    headerMsg->Unpack();

    statMsg->SetMessageHeader(headerMsg);
    statMsg->AllocatePack();
 
    // Receive data from the socket
    socket->Receive(statMsg->GetPackBodyPointer(), statMsg->GetPackBodySize());
 
    statMsg->Unpack();

    if (statMsg->GetCode() == 2) // correct code from slicer
          {
             if (strcmp(statMsg->GetStatusString(), "SlicerHandshake") == 0)
              {
                 //successful connection
                 return 1;
              }

             else
             {
                 return 0;
             }
          }
    else
    {
        return 0;
    }

}

/*
igtl::StatusMessage::Pointer window1::getStatMsg()
{
    return statMsg;
}

*/


