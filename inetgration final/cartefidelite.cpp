#include "cartefidelite.h"

CarteFidelite::CarteFidelite()
{
    numCarte=0;
    date_de_creation="";
    points=0;
    totalAchats=0;
    statut="";
    remise=0;
    matriculeFiscale="";



}

CarteFidelite::CarteFidelite(int numCarte,QString date_de_creation,int points,double totalAchats,QString statut,int remise,QString matriculeFiscale)
{
    this->numCarte=numCarte;
    this->date_de_creation=date_de_creation;
    this->points=points;
    this->totalAchats=totalAchats;
    this->statut=statut;
    this->remise=remise;
   this->matriculeFiscale=matriculeFiscale;

 }
 QSqlQueryModel * CarteFidelite::afficher()
 {
     QSqlQueryModel * modal=new QSqlQueryModel();
     modal->setQuery("SELECT * FROM CARTE_FIDELITE");

     return modal;

 }



 bool CarteFidelite::ajouter()
 {

     QSqlQuery query;

     query.prepare("INSERT INTO CARTE_FIDELITE (NUM_CARTE, DATE_DE_CREATION, POINTS, TOTAL_ACHATS, STATUT,REMISE,MATRICULE_FISCALE) "
                         "VALUES (:numCarte, :date_de_creation, :points,:totalAchat,:statut,:remise,:matricule_fiscale)");
     query.bindValue(":numCarte",numCarte );
     query.bindValue(":date_de_creation",date_de_creation); //remplir la valeur d'une maniere securisée
     query.bindValue(":points", points);
     query.bindValue(":totalAchat", totalAchats);
     query.bindValue(":statut",statut);
     query.bindValue(":remise",remise);
     query.bindValue(":matricule_fiscale",matriculeFiscale);

     return    query.exec();


 }

  bool CarteFidelite::modifier()
  {


      QSqlQuery query;

      query.prepare(" UPDATE CARTE_FIDELITE SET NUM_CARTE=:numCarte, DATE_DE_CREATION=:date_de_creation,"
                    " POINTS=:points, TOTAL_ACHATS=:totalAchats, STATUT=:statut,REMISE=:remise"
                    " WHERE NUM_CARTE=:numCarte ");
      query.bindValue(":numCarte",numCarte );
      query.bindValue(":date_de_creation",date_de_creation); //remplir la valeur d'une maniere securisée
      query.bindValue(":points", points);
      query.bindValue(":totalAchats", totalAchats);
      query.bindValue(":statut",statut);
      query.bindValue(":remise",remise);

      return    query.exec();

  }


  bool CarteFidelite::supprimer()
  {
      QSqlQuery query;
      query.prepare("Delete from CARTE_FIDELITE where NUM_CARTE=:numCarte");
      query.bindValue(":numCarte",numCarte);
      return    query.exec();


  }





