#include "produit.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

Produit::Produit()
{
    Quantite=0;
    Prix=0;
    Dimensions=0;
    Poids=0;
    Volume=0;
    Categorie="";
    Description="";
    Reference="";
    Emplacement="";
    Date_de_creation="jj/mm/aaaa";
    Date_d_expiration="jj/mm/aaaa";
    Commentaire="";
}

Produit::Produit(int Quantite,double Prix,double Dimensions,double Poids,double Volume,QString Categorie,QString Description,QString Reference,QString Emplacement,QString Date_de_creation,QString Date_d_expiration,QString Commentaire)
{
    this->Quantite=Quantite;
    this-> Prix=Prix;
    this->Dimensions=Dimensions;
    this->Poids=Poids;
    this->Volume=Volume;
    this-> Categorie=Categorie;
    this-> Description=Description;
    this->Reference=Reference;
    this->Emplacement=Emplacement;
    this->Date_de_creation=Date_de_creation;
    this->Date_d_expiration=Date_d_expiration;
    this->Commentaire=Commentaire;
}
 bool Produit::ajouterProduit()
 {

 QSqlQuery query;

       query.prepare("INSERT INTO PRODUIT (CATEGORIE, DESCRIPTION, REFERENCE, QUANTITE, DATE_DE_CREATION, DATE_D_EXPIRATION,EMPLACEMENT, PRIX, DIMENSIONS, POIDS, VOLUME,COMMENTAIRE) "
                     "VALUES (:CATEGORIE, :DESCRIPTION, :REFERENCE, :QUANTITE, :DATE_DE_CREATION, :DATE_D_EXPIRATION,:EMPLACEMENT, :PRIX, :DIMENSIONS, :POIDS, :VOLUME,:COMMENTAIRE)");
       query.bindValue(0, Categorie);
       query.bindValue(1, Description);
       query.bindValue(2, Reference);
       query.bindValue(3, Quantite);
       query.bindValue(4, Date_de_creation);
       query.bindValue(5, Date_d_expiration);
       query.bindValue(6, Emplacement);
       query.bindValue(7, Prix);
       query.bindValue(8, Dimensions);
       query.bindValue(9, Poids);
       query.bindValue(10, Volume);
       query.bindValue(11, Commentaire);

       return query.exec();

 }

 QSqlQueryModel* Produit::afficherProduit()
 {
      QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM PRODUIT");

       return model;

 }

 bool Produit::supprimerProduit(QString Reference)
 {

      QSqlQuery query;

     query.prepare("select * from produit where reference=:Reference");
     query.bindValue(0, Reference);
     query.exec();
     if(query.exec() && query.next())
     {

     query.prepare("delete from produit where reference=:Reference");
     query.bindValue(0, Reference);
     return query.exec();

     }
     return false;


 }

 bool  Produit::modifierProduit()
 {

     QSqlQuery query;

           query.prepare("UPDATE PRODUIT SET CATEGORIE=:Categorie,DESCRIPTION=:Description, REFERENCE=:Reference"
                         ", QUANTITE=:Quantite, DATE_DE_CREATION=:Date_de_creation, DATE_D_EXPIRATION=:Date_d_expiration"
                         ", EMPLACEMENT=:Emplacement, PRIX=:Prix, DIMENSIONS=:Dimensions, POIDS=:Poids"
                         ", VOLUME=:Volume,COMMENTAIRE=:Commentaire WHERE REFERENCE=:Reference ");
           query.bindValue(":Categorie", Categorie);
           query.bindValue(":Description", Description);
           query.bindValue(":Reference", Reference);
           query.bindValue(":Quantite", Quantite);
           query.bindValue(":Date_de_creation", Date_de_creation);
           query.bindValue(":Date_d_expiration", Date_d_expiration);
           query.bindValue(":Emplacement", Emplacement);
           query.bindValue(":Prix", Prix);
           query.bindValue(":Dimensions", Dimensions);
           query.bindValue(":Poids", Poids);
           query.bindValue(":Volume", Volume);
           query.bindValue(":Commentaire", Commentaire);
           return query.exec();
 }


 bool Produit::affecterMP(QString RefMP)
 {
 QSqlQuery query;
 query.prepare("INSERT INTO COMPOSITION (REF_PRODUIT, REF_MP)"
               "VALUES (:refP,:refMP)");
 query.bindValue(":refP", Reference);
 query.bindValue(":refMP", RefMP);
 return query.exec();
 }


 QSqlQueryModel* Produit::afficher_MPaffecte()
 {
   QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("select REF_MP from COMPOSITION where REF_PRODUIT = '"+Reference+"'");
    return model;

 }


 bool Produit::suppAffectation(QString refMP)
 {
     QSqlQuery query;

    query.prepare("delete from COMPOSITION where REF_MP=:refmp");
    query.bindValue(":refmp", refMP);

    return query.exec();

 }


