#include "connection.h"
#include <QDebug>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Application");
db.setUserName("rihem");//inserer nom de l'utilisateur
db.setPassword("rihem");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

qDebug()<<db.lastError().text();



    return  test;
}
