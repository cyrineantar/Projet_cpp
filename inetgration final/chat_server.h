#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <QDialog>
#include <QTcpSocket>
#include<QTcpServer>

namespace Ui {
class chat_server;
}

class chat_server : public QDialog
{
    Q_OBJECT

public:
    explicit chat_server(QWidget *parent = nullptr);
    ~chat_server();

private slots:
    void on_pushButton_Listen_clicked();

    void on_pushButton_Send_clicked();

    void server_New_Connect();
    void socket_Recv_Data();
    void socket_Disconnect();


    //void on_pushButton_clicked();

private:
    Ui::chat_server *ui;
    QTcpServer *m_server;
    QTcpSocket *m_socket;
};

#endif // CHAT_SERVER_H
