 #include "machine.h"
#include <QSqlQuery>
#include <QDebug>

machine::machine()
{
 code="";
 type="";
 date="";
 puissance="";
 consommation="";
}
machine::machine(QString code,QString date,QString type,QString puissance,QString consommation)
{
 this->code =code;
    this->date =date;
    this->type =type;
    this->puissance =puissance;
    this->consommation =consommation;
}
void machine::setcode(QString n){code=n;}
void machine::setdate(QString n){date=n;}
void machine::settype(QString n){type=n;}
void machine::setpuissance(QString n){puissance=n;}
void machine::setconsommation(QString n){consommation=n;}

QString machine::get_code(){return code;}
QString machine::get_date(){return date;}
QString machine::get_type(){return type;}
QString machine::get_puissance(){return puissance;}
QString machine::get_consommation(){return consommation;}
bool machine::ajouter()
{

    QSqlQuery query;
      query.prepare("INSERT INTO machine (CODE,DATEM,TYPE,CONSOMMATION,PUISSANCE) "
                    "VALUES (:code,:date, :type, :consommation, :puissance)");
      query.bindValue(":code", code);
       query.bindValue(":date", date);
      query.bindValue(":type", type);
      query.bindValue(":consommation", consommation);
       query.bindValue(":puissance", puissance);



      return query.exec();
}

QSqlQueryModel* machine::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM machine");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("consommation"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("puissance"));


  return  model;
}
bool machine::supprimer(QString code)
{
    QSqlQuery query;
         query.prepare(" Delete from machine where code=:code");
         query.bindValue(0, code);

        return query.exec();


}
