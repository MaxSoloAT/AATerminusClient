#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectToServer(QString ip, int port);
    void setIP(QString ip);
    void setPort(int port);

public slots:
    void socketReady();
    void socketDisconnected();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket = nullptr;
    QString localhost = "127.0.0.1";
    int port = 1331;
    QString ip = "";
    QByteArray Data;
};
#endif // MAINWINDOW_H
