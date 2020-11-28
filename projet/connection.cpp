#include "connection.h"
#include <QDebug>
connection::connection()
{

}

bool connection::createconnection(){
    bool test=false;
    QSqlDatabase db =QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_2A");
    db.setUserName("Aziz");
    db.setPassword("aziz1234");
    if (db.open())
        test=true;
    qDebug()<<db.lastError().text();

    return test;
}
