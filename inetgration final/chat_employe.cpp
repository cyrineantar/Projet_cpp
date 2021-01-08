#include "chat_employe.h"
#include "ui_chat_employe.h"

#include<QMessageBox>
#include <QTime>
chat_employe::chat_employe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat_employe)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat employe");
    m_socket=new QTcpSocket();

        QObject::connect(m_socket,&QTcpSocket::readyRead,this,&chat_employe::sockt_recv_data);
        QObject::connect(m_socket,&QTcpSocket::disconnected,this,&chat_employe::socket_disconnect);

        ui->pushButton_Send->setShortcut(QKeySequence(tr("ctrl+return")));

        ui->lineEdit_IP->setText("127.0.0.1");
        ui->lineEdit_Port->setText("1234");
        ui->pushButton_Send->setEnabled(false);
    }

chat_employe::~chat_employe()
    {
        delete m_socket;
        delete ui;
    }

  void chat_employe::on_pushButton_Connect_clicked()
    //Connect button
    {
        QString IP;
        qint16 port;

        if (ui->pushButton_Connect->text() == QString("connection"))
        {
            IP=ui->lineEdit_IP->text();
            port=ui->lineEdit_Port->text().toInt();

            m_socket->abort();
            m_socket->connectToHost(IP,port);

                if (!m_socket->waitForConnected())
                    {

                        QMessageBox msgBox;
                         msgBox.setText("Connection timed out！");
                         msgBox.resize(40,30);
                         msgBox.exec();
                        return;
                    }

             QMessageBox msgBox;
              msgBox.setText("connection succeeded！");
              msgBox.resize(40,30);
              msgBox.exec();

            ui->pushButton_Send->setEnabled(true);
            ui->pushButton_Connect->setText("Disconnect");

           }
        else
        {
            m_socket->disconnectFromHost();
            ui->pushButton_Connect->setText("connection");
            ui->pushButton_Send->setEnabled(false);
        }
    }

    void chat_employe::on_pushButton_Send_clicked()
    //Send button
    {
        if (ui->textEdit->toPlainText()== QString())
       //Empty message detection
        {
            QMessageBox msgb;
            msgb.setText("Cannot send empty message！");
            msgb.resize(60,40);
            msgb.exec();
            return;
        }
        ui->textBrowser->setTextColor(Qt::gray);
        ui->textBrowser->setCurrentFont(QFont("Times New Roman",10));
        ui->textBrowser->append("From employe:  "+QTime::currentTime().toString());

         ui->textBrowser->setTextColor(Qt::black);
         ui->textBrowser->setCurrentFont(QFont("Times New Roman",16));
        ui->textBrowser->append(ui->textEdit->toPlainText().toUtf8());

        m_socket->write(ui->textEdit->toPlainText().toUtf8());
        m_socket->flush();
        ui->textEdit->clear();
    }

 void chat_employe:: sockt_recv_data()
    {
        QByteArray data_tmp;
        data_tmp = m_socket->readAll();
        if (!data_tmp.isEmpty())
        {
            //QString str = ui->textBrowser->toPlainText();

            QString str=QString(data_tmp);

            ui->textBrowser->setTextColor(Qt::gray);
            ui->textBrowser->setCurrentFont(QFont("Times New Roman",10));
            ui->textBrowser->append("From Server:  "+QTime::currentTime().toString());

             ui->textBrowser->setTextColor(Qt::black);
             ui->textBrowser->setCurrentFont(QFont("Times New Roman",16));
            ui->textBrowser->append(str);



        }
    }

    void chat_employe:: socket_disconnect()
    {
        ui->pushButton_Send->setEnabled(false);
        ui->pushButton_Connect->setText("connection");
        QMessageBox msgBox;
         msgBox.setText("Disconnect！");
         msgBox.resize(40,30);
         msgBox.exec();
    }

