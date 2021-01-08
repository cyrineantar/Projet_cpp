

#ifndef CHAT_EMPLOYE_H
#define CHAT_EMPLOYE_H

#include <QDialog>
#include <QTcpSocket>
namespace Ui {
class chat_employe;
}

class chat_employe : public QDialog
{
    Q_OBJECT

public:
    explicit chat_employe(QWidget *parent = nullptr);
    ~chat_employe();
private slots:
    void on_pushButton_Connect_clicked() ;  // Connect button
    void on_pushButton_Send_clicked() ; //  Send button

    void sockt_recv_data();
    void socket_disconnect();
private:
    Ui::chat_employe *ui;
     QTcpSocket *m_socket;
};


#endif // CHAT_EMPLOYE_H
