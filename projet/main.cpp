#include "mainwindow.h"
#include "connexion.h"
#include <QMessageBox>
#include <QTextToSpeech>
#include <QApplication>
#include <QFile>
#include "stock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        Connexion c;
        bool test=c.ouvrirConnexion();
        MainWindow w;
        //open qss file
        QFile File(":/Combinear.qss");
        File.open(QFile::ReadOnly);
        QString StyleSheet =QLatin1String(File.readAll());
        //setup stylesheet
        a.setStyleSheet(StyleSheet);

        if(test)
        {
            w.show();
            QTextToSpeech * m_speech =new QTextToSpeech();
            m_speech->say("la base de données est ouverte avec succès");
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click ok to exit."), QMessageBox::Close);


        }
        else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click ok to exit."), QMessageBox::Close);


    return a.exec();
}
