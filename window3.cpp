#include "window3.h"
#include <QDebug>

window3::window3(QWidget *parent):
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

    font1 = new QFont("", .04 *screenH, 25, false);
    font1 -> setFamily(font1 -> defaultFamily());

    font2 = new QFont("", .025*screenH, 25, false);
    font2 -> setFamily(font2 -> defaultFamily());

    title = new QLabel(this, 0);
    QPalette textPal = title->palette();
    textPal.setColor(QPalette::WindowText, Qt::gray);
    title -> setGeometry((3*screenW)/7,(41*screenH/600), screenW/2, screenH/15 );
    title ->setFont(*font1);
    title -> setPalette(textPal);
   // title -> setText("Target 1");

    tarCancel = new QLabel("              Cancelled", this, 0);
    QPalette cancelPal = tarCancel -> palette();
    cancelPal.setColor(QPalette::WindowText, Qt::red);;
    tarCancel->setGeometry((3*screenW)/7,(41*screenH/600), screenW/2, screenH/15);
    tarCancel->setFont(*font1);
    tarCancel -> setPalette(cancelPal);
    tarCancel -> setVisible(false);

    depth = new QLabel("" ,this,0);
    depth -> setGeometry((23*screenW)/56,(2*screenH/15), screenW/2, screenH/15 );
    depth -> setFont(*font1);
    depth -> setPalette(textPal);

    back = new QPushButton("Go back", this);
    back -> setGeometry(screenW/100, screenH/50, screenW/5, screenH/6);
    back -> setFont(*font1);

    /*
    send = new QPushButton("Send target to robot", this);
    send -> setGeometry (screenW/10, screenH/4, screenW/5, screenH/6);
    send -> setFont(*font2);
    */

    move = new QPushButton("Move robot", this);
    move -> setGeometry((screenW)/10, screenH/4, (7*screenW)/20, screenH/5);
    move -> setFont(*font1);
    //move -> setEnabled(false);

    cancel = new QPushButton("Cancel target", this);
    cancel -> setGeometry((11*screenW)/20, screenH/4, (7*screenW)/20, screenH/5);
    cancel -> setFont(*font1);
    //cancel -> setEnabled(false);

    connect(back, SIGNAL (clicked()), this, SIGNAL (moveToWindow2()));
    connect(back, SIGNAL(clicked()), this, SLOT(hide()));
    connect(back, SIGNAL(clicked()), this, SLOT(reset()));
    //connect(send, SIGNAL(clicked()), this, SLOT(sendMsg()));
    //connect(send, SIGNAL(clicked()), this,  SLOT(targetSent()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelled()));
    connect(move, SIGNAL(clicked()), this, SLOT(moveSent()));
}

void window3::getTargetNum(int num, const char* depthVal)
{
    targetNum = num;
    //qDebug()<<"depthVal: " << + depthVal;
    targetDepth = atoi(depthVal);

    setWindowTitle("Target "+QString::number(num));
    title->setText("Target " +QString::number(num));
    depth -> setText("Depth: " + QString::number(targetDepth));

}

void window3::recSocket(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg)
{
    socket = igtl::ClientSocket::New();
    socket = sckt;
    qDebug() <<"socket3: " << socket;

    statMsg = igtl::StatusMessage::New();
    statMsg = msg;
    qDebug() <<"statMsg3: " << statMsg;
}


/*
void window3::sendMsg()
{
    strMsg = igtl::StringMessage::New();
    ts = igtl::TimeStamp::New();
    strMsg->SetDeviceName("Interface");

    if (targetNum == 0)
    {
        msg = "Error, no target selected";
    }

    if (targetNum == 1)
    {
        msg = "Target 1";
     }

    else if(targetNum == 2)
    {
        msg = "Target 2";
    }

    else if(targetNum == 3)
    {
        msg = "Target 3";
    }

     ts->GetTime();
     strMsg->SetString(msg);
     strMsg->SetTimeStamp(ts);
     strMsg->Pack();

     socket->Send(strMsg->GetPackPointer(), strMsg->GetPackSize());
}
*/

void window3::targetSent()
{
    send -> setText("Target sent");
    send -> setFont(*font1);
    send -> setEnabled(false);

    move -> setEnabled(true);
    cancel -> setEnabled(true);
    back -> setEnabled(false);
}

void window3::cancelled()
{
    /*
    send -> setText("Send target to robot");
    send -> setFont(*font2);
    send -> setEnabled(true);
    */
    statMsg -> SetCode(1);
    statMsg -> SetStatusString("CancelTarget");
    statMsg->Pack();
    socket->Send(statMsg->GetPackPointer(), statMsg->GetPackSize());

    move -> setText("Move robot");
    move -> setEnabled(false);

    cancel -> setEnabled(false);

    back -> setEnabled(true);

    tarCancel -> setVisible(true);
}

void window3::moveSent()
{
    //receive status from robot
    statMsg -> SetCode(1);
    statMsg -> SetStatusString("MoveRobot");
    statMsg->Pack();
    socket->Send(statMsg->GetPackPointer(), statMsg->GetPackSize());
    qDebug()<<"move socket: "<<socket;
    qDebug()<<"move statMsg: "<<statMsg;


    move -> setText("Ready to move");
    move -> setEnabled(false);

    back -> setEnabled(true);
}

void window3::reset()
{
    statMsg -> SetCode(1);
    statMsg -> SetStatusString("CancelTarget");
    statMsg->Pack();
    socket->Send(statMsg->GetPackPointer(), statMsg->GetPackSize());

    move -> setEnabled(true);
    tarCancel -> setVisible(false);
    cancel -> setEnabled(true);
}
