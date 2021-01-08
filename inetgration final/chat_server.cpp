#include "chat_server.h"
#include "ui_chat_server.h"

#include <QtWidgets/QMessageBox>
#include <QTime>


chat_server::chat_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat_server)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat Server");
    ui->lineEdit_Port->setText("1234");
    ui->pushButton_Send->setEnabled(false);


    m_server = new QTcpServer();

    connect(m_server,&QTcpServer::newConnection,this,&chat_server::server_New_Connect);

}

chat_server::~chat_server()
{
    m_server->close();
    m_server->deleteLater();
    delete ui;
}

 void chat_server::server_New_Connect()
 {
   //Get client connection
    m_socket = m_server->nextPendingConnection();

    QObject::connect(m_socket,&QTcpSocket::readyRead,this,&chat_server::socket_Recv_Data);
    QObject::connect(m_socket,&QTcpSocket::disconnected,this,&chat_server::socket_Disconnect);

    ui->textBrowser->setTextColor(Qt::gray);
    ui->textBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->textBrowser->append(tr("Clientconnection！%1\n").arg(QTime::currentTime().toString()));

    ui->pushButton_Send->setEnabled(true);

 }

void chat_server:: socket_Recv_Data()
{
    QByteArray data_tmp;
    data_tmp = m_socket->readAll();
    if(!data_tmp.isEmpty())
    {
        QString str = QString(data_tmp);

        ui->textBrowser->setTextColor(Qt::gray);
        ui->textBrowser->setCurrentFont(QFont("Times New Roman",10));
        ui->textBrowser->append("From employe:  "+QTime::currentTime().toString());

         ui->textBrowser->setTextColor(Qt::black);
         ui->textBrowser->setCurrentFont(QFont("Times New Roman",16));
        ui->textBrowser->append(str);

        QTextCursor cursor = ui->textBrowser->textCursor(); //Automatically drop down to the bottom
        cursor.movePosition(QTextCursor::End);
        ui->textBrowser->setTextCursor(cursor);
    }
}

void chat_server:: socket_Disconnect()
{
    ui->pushButton_Send->setEnabled(false);
    ui->textBrowser->setTextColor(Qt::gray);
    ui->textBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->textBrowser->append(tr("Client  go away！%1\n").arg(QTime::currentTime().toString()));


}

void chat_server::on_pushButton_Listen_clicked()
{
    if (ui->pushButton_Listen->text() ==QString("monitor"))
        {
        qint16 port = ui->lineEdit_Port->text().toInt();

        if(!m_server->listen(QHostAddress::Any, port))
        {
            QMessageBox::critical(this,"Error！",m_server->errorString(),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes );
            return;

        }
        ui->pushButton_Listen->setText("Unlisten");


    }
    else
    {
        if(m_socket->state() == QAbstractSocket::ConnectedState)
        {
            m_socket->disconnectFromHost();
        }
        m_server->close();

        ui->pushButton_Listen->setText("monitor");
        ui->pushButton_Send->setEnabled(false);
    }
}

void chat_server::on_pushButton_Send_clicked()
{
    if (ui->textEdit->toPlainText() == QString())
    {
        QMessageBox msgb;
        msgb.setText("Cannot send empty message！");
        msgb.resize(60,40);
        msgb.exec();
        return;
    }
    m_socket->write(ui->textEdit->toPlainText().toUtf8());

    ui->textBrowser->setTextColor(Qt::gray);
    ui->textBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->textBrowser->append("From Server:  "+QTime::currentTime().toString());

     ui->textBrowser->setTextColor(Qt::black);
     ui->textBrowser->setCurrentFont(QFont("Times New Roman",16));
    ui->textBrowser->append(ui->textEdit->toPlainText().toUtf8());
    m_socket->flush();
    ui->textEdit->clear();


}
