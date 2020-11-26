#include "connection.h"
#include <QDebug>

//test tutoriel git

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("Cyrine");//inserer nom de l'utilisateur
db.setPassword("cyrine1");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
qDebug()<<db.lastError().text();


    return  test;
}
