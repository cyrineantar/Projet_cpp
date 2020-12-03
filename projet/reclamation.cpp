#include "reclamation.h"
#include "machine.h"
#include <QSqlQuery>
#include <QDebug>

reclamation::reclamation()
{
     date_panne="";
     cause_panne="";
     codeM="";
}

reclamation::reclamation(QString date_panne,QString cause_panne,QString codeM)
{
 this->date_panne =date_panne;
    this->cause_panne =cause_panne;
    this->codeM =codeM;

}

void reclamation::setdate_panne(QString n){date_panne=n;}
void reclamation::setcause_panne(QString n){cause_panne=n;}
void reclamation::setcodeM(QString n){codeM=n;}

QString reclamation::get_date_panne(){return date_panne;}
QString reclamation::get_cause_panne(){return cause_panne;}
QString reclamation::get_codeM(){return codeM;}

bool reclamation::ajouter()
{

    QSqlQuery query;
      query.prepare("INSERT INTO reclamation (DATE_PANNE,CAUSE_PANNE,CODEM) "
                    "VALUES (:date_panne,:cause_panne,:codeM)");
      query.bindValue(":date_panne", date_panne);
       query.bindValue(":cause_panne", cause_panne);
       query.bindValue(":codeM",codeM);



      return query.exec();
}

QSqlQueryModel* reclamation::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM reclamation");



  return  model;
}
bool reclamation::supprimer(QString codeM)
{
    QSqlQuery query;
         query.prepare(" Delete from reclamation where codeM=:codeM");
         query.bindValue(0, codeM);

        return query.exec();


}
bool reclamation::modifier(QString codeM, QString date_panne,QString cause_panne)
{
    QSqlQuery query;
         query.prepare(" update reclamation set date_panne='"+date_panne+"' ,cause_panne='"+cause_panne+"'where codeM ='"+codeM+"'");
         return query.exec();
}


QSqlQueryModel* reclamation::rechercher(QString colone,QString text)
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM reclamation WHERE UPPER("+colone+") LIKE UPPER('"+text+"%')");

     return model;
}


QSqlQueryModel*  reclamation::tri(QString colone, QString ordre)
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("select * from reclamation order by "+colone+" "+ordre+"");
return model;
}

