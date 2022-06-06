#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
    ip = localhost;

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

