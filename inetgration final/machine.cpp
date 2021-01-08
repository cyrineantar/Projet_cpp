#include "machine.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMediaPlayer>

machine::machine()
{
code="";
date="";
fonctionnement="";
puissance="";
}


machine::machine(QString code,QString date,QString fonctionnement,QString puissance)
{
   this->code =code;
   this->date =date;
   this->fonctionnement =fonctionnement;
   this->puissance =puissance;
}


void machine::setcode(QString n){code=n;}
void machine::setdate(QString n){date=n;}
void machine::setfonctionnement(QString n){fonctionnement=n;}
void machine::setpuissance(QString n){puissance=n;}


QString machine::get_code(){return code;}
QString machine::get_date(){return date;}
QString machine::get_fonctionnement(){return fonctionnement;}
QString machine::get_puissance(){return puissance;}


bool machine::ajouter()
{

   QSqlQuery query;
     query.prepare("INSERT INTO machine (CODE,DATEM,FONCTIONNEMENT,PUISSANCE) "
                   "VALUES (:code,:date, :fonctionnement, :puissance)");
     query.bindValue(":code", code);
      query.bindValue(":date", date);
     query.bindValue(":fonctionnement", fonctionnement);
      query.bindValue(":puissance", puissance);



     return query.exec();
}


QSqlQueryModel* machine::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();


  model->setQuery("SELECT* FROM machine");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("fonctionnement"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("puissance"));



 return  model;
}
bool machine::supprimer(QString code)
{
   QSqlQuery query;
        query.prepare(" Delete from machine where code=:code");
        query.bindValue(0, code);

       return query.exec();


}

bool machine::modifier(QString code,QString date,QString fonctionnement,QString puissance)
{
   QSqlQuery query;
        query.prepare(" update machine set dateM='"+date+"' ,fonctionnement='"+fonctionnement+"' ,puissance='"+puissance+"'where code ='"+code+"'");
        return query.exec();
}

QSqlQueryModel* machine::rechercher(QString colone1,QString text)
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM machine WHERE UPPER("+colone1+") LIKE UPPER('"+text+"%')");

    return model;
}

QSqlQueryModel*  machine::tri(QString colone, QString ordre)
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("select * from machine order by "+colone+" "+ordre+"");
return model;
}
