#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <string>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
    ip = "192.168.89.90";
    //ip = localhost;
    qDebug()<<ip<<endl;
    localhost = "";
    qDebug()<<ip<<endl;

    connectToServer(ip,port);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToServer(QString ip, int port)
{
    socket->connectToHost(ip,port);
}

void MainWindow::setIP(QString ip)
{
    this->ip = ip;
}

void MainWindow::setPort(int port)
{
    this->port = port;
}

void MainWindow::socketReady()
{
    if(socket->waitForConnected(500)){
        socket->waitForReadyRead(200);
        Data = socket->readAll();
        qDebug()<<Data<<endl;
        ui->label->setText(Data);
    }
}

void MainWindow::socketDisconnected()
{
    socket->deleteLater();
}


void MainWindow::on_pushButton_clicked()
{
    QString predata = ui->lineEdit->text();
    QByteArray Data1 = QByteArray::fromStdString(predata.toStdString());
    qDebug()<<Data1<<endl;
    socket->write(Data1);

}


void MainWindow::on_pushButton_2_clicked()
{
   QVector<std::string> dat = {"$120=2|$120=2|$120=2|$120=2",
                            "G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X0 Y0 Z0",
                            "G0 X8 Y-10 Z0|G0 X8 Y-10 Z0|G0 X-8 Y10 Z0|G0 X-8 Y10 Z0",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z-2.8|G0 X-8 Y10 Z-2.8",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z-2.8|G0 X-8 Y10 Z0",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z-2.8|G0 X-2 Y2 Z0",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z-2.8|G0 X-2 Y2 Z-2.8",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z0|G0 X-2 Y2 Z-2.8",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-13 Y13 Z0|G0 X-2 Y2 Z-2.8",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-13 Y13 Z-2.8|G0 X-2 Y2 Z-2.8",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z0|G0 X-13 Y13 Z-2.8|G0 X-2 Y2 Z-2.8",
                            "G0 X8 Y-10 Z-2.8|G0 X2 Y-2 Z0|G0 X-13 Y13 Z-2.8|G0 X-2 Y2 Z-2.8",
                            "G0 X8 Y-10 Z-2.8|G0 X2 Y-2 Z-2.8|G0 X-13 Y13 Z-2.8|G0 X-2 Y2 Z-2.8",

                            "G0 X8 Y-10 Z0|G0 X2 Y-2 Z-2.8|G0 X-13 Y13 Z-2.8|G0 X-2 Y2 Z-2.8",
                            "G0 X13 Y-13 Z0|G0 X2 Y-2 Z-2.8|G0 X-13 Y13 Z-2.8|G0 X-2 Y2 Z-2.8",
                            "G0 X13 Y-13 Z-2.8|G0 X2 Y-2 Z-2.8|G0 X-13 Y13 Z-2.8|G0 X-2 Y2 Z-2.8",
                            "G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z-2.8|G0 X-8 Y10 Z-2.8"
                           };

    socket->write(QByteArray::fromStdString(dat[curr]));
    curr++;
    if(curr == dat.size()-1){curr=0;}
    /*socket->write(QByteArray::fromStdString("$120=2|$120=2|$120=2|$120=2|"));
    socket->waitForBytesWritten(1000);
    std::cin>>a;
    socket->write(QByteArray::fromStdString("G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X0 Y0 Z0|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X8 Y-10 Z0|G0 X8 Y-10 Z0|G0 X-8 Y10 Z0|G0 X-8 Y10 Z0|"));
    socket->waitForBytesWritten(1000);

    socket->write(QByteArray::fromStdString("G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z-2.8|G0 X-8 Y10 Z-2.8|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z-2.8|G0 X-8 Y10 Z0|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X8 Y-10 Z-2.8|G0 X8 Y-10 Z-2.8|G0 X-8 Y10 Z-2.8|G0 X-2 Y2 Z0|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X8 Y-10 Z0|G0 X8 Y-10 Z0|G0 X-8 Y10 Z0|G0 X-2 Y2 Z-2.8"));
    socket->waitForBytesWritten(1000);

*/

    /*
    socket->write(QByteArray::fromStdString("G0 X-6 Y4 Z0|G0 X-6 Y4 Z0|G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X-6 Y4 Z-2.8|G0 X-6 Y4 Z-2.8|G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X-6 Y4 Z-2.8|G0 X-6 Y4 Z-2.8|G0 X0 Y0 Z0|G0 X0 Y0 Z0|"));
    socket->waitForBytesWritten(1000);

    socket->write(QByteArray::fromStdString("G0 X-6 Y4 Z-2.8|G0 X-6 Y4 Z-2.8|G0 X6 Y-2 Z0|G0 X6 Y-2 Z0|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X-6 Y4 Z-2.8|G0 X-6 Y4 Z-2.8|G0 X6 Y-2 Z-2.8|G0 X6 Y-2 Z-2.8|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X-6 Y4 Z0|G0 X-6 Y4 Z0|G0 X6 Y-2 Z-2.8|G0 X6 Y-2 Z-2.8|"));
    socket->waitForBytesWritten(1000);

    socket->write(QByteArray::fromStdString("G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X6 Y-2 Z-2.8|G0 X6 Y-2 Z-2.8|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|G0 X6 Y-2 Z-2.8|G0 X6 Y-2 Z-2.8|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|G0 X6 Y-2 Z0|G0 X6 Y-2 Z0|"));
    socket->waitForBytesWritten(1000);

    socket->write(QByteArray::fromStdString("G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|G0 X0 Y0 Z0|G0 X0 Y0 Z0|"));

    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|"));
    socket->waitForBytesWritten(1000);
    socket->write(QByteArray::fromStdString("G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X0 Y0 Z0|"));
    socket->waitForBytesWritten(1000);
    }






socket->write(QByteArray::fromStdString("G0 X-12 Y-6 Z0|G0 X-12 Y-6 Z0|G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|"));
    socket->write(QByteArray::fromStdString("G0 X-12 Y-6 Z-2.8|G0 X-12 Y-6 Z-2.8|G0 X0 Y0 Z-2.8|G0 X0 Y0 Z-2.8|"));
    socket->write(QByteArray::fromStdString("G0 X-12 Y-6 Z-2.8|G0 X-12 Y-6 Z-2.8|G0 X0 Y0 Z0|G0 X0 Y0 Z0|"));

    socket->write(QByteArray::fromStdString("G0 X-12 Y-6 Z-2.8|G0 X-12 Y-6 Z-2.8|G0 X12 Y6 Z0|G0 X12 Y6 Z0|"));
    socket->write(QByteArray::fromStdString("G0 X-12 Y-6 Z-2.8|G0 X-12 Y-6 Z-2.8|G0 X12 Y6 Z-2.8|G0 X12 Y6 Z-2.8|"));

    socket->write(QByteArray::fromStdString("G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X0 Y0 Z0|G0 X0 Y0 Z0|"));*/
}

