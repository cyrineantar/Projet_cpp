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

void reclamation::setcause_panne(QString n){cause_panne=n;}
void reclamation::setdate_panne(QString n){date_panne=n;}
void reclamation::setcodeM(QString n){codeM=n;}

QString reclamation::get_cause_panne(){return cause_panne;}
QString reclamation::get_date_panne(){return date_panne;}
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
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_panne"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("cause_panne"));
   model->setHeaderData(0, Qt::Horizontal,QObject::tr("codeM"));
  // ui->tableView_2->horizontalHeader()->setSectionsClickable(1);

  return  model;
}
bool reclamation::supprimer(QString codeM)
{
    QSqlQuery query;
         query.prepare(" Delete from reclamation where codeM=:codeM");
         query.bindValue(0, codeM);

        return query.exec();


}
bool reclamation::modifier(QString codeM)
{
    QSqlQuery query;
         query.prepare(" update reclamation set CAUSE_PANNE='"+cause_panne+"',DATE_PANNE='"+date_panne+"' where CODEM ='"+codeM+"'");
         return query.exec();
}
