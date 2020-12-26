#include "matierepremiere.h"

MatierePremiere::MatierePremiere()
{
    reference="";
    description="";
    emplacement="";
    quantite=0;
    prix=0;
    dateAchat="";
    poids=0;
    volume=0;
    commentaire="";
}


MatierePremiere::MatierePremiere(QString reference,QString description,QString emplacement,int quantite,double prix,QString dateAchat,double poids,double volume,QString commentaire)
{
    this->reference=reference;
    this->description=description;
    this->emplacement=emplacement;
    this->quantite=quantite;
    this->prix=prix;
    this->dateAchat=dateAchat;
    this->poids=poids;
    this->volume=volume;
    this->commentaire=commentaire;

}


QSqlQueryModel* MatierePremiere:: afficherMP()
{
    QSqlQueryModel* model=new QSqlQueryModel();
     model->setQuery("SELECT * from mp ");
     return model;
}

bool MatierePremiere::ajouterMP()
{
    QSqlQuery query;

          query.prepare("INSERT INTO MP (REFERENCE, DESCRIPTION, EMPLACEMENT, QUANTITE, PRIX, DATE_ACHAT, POIDS, VOLUME,COMMENTAIRE) "
                        "VALUES (:REFERENCE, :DESCRIPTION, :EMPLACEMENT, :QUANTITE, :PRIX, :DATE_ACHAT,:POIDS, :VOLUME,:COMMENTAIRE)");
          query.bindValue(0, reference);
          query.bindValue(1, description);
          query.bindValue(2, emplacement);
          query.bindValue(3, quantite);
          query.bindValue(4, prix);
          query.bindValue(5, dateAchat);
          query.bindValue(6, poids);
          query.bindValue(7, volume);
          query.bindValue(8, commentaire);

          return query.exec();
}


 bool MatierePremiere::supprimerMP(QString Reference)
 {
     QSqlQuery query;
     query.prepare("SELECT * from mp where reference=:Reference");
     query.bindValue(0, Reference);
        query.exec();
     if(query.exec() && query.next())
     {
    query.prepare("delete from mp where reference=:Reference");
    query.bindValue(0, Reference);
    return query.exec();
     }
     else return false;
 }

 bool MatierePremiere::modifierMP()
 {
     QSqlQuery query;

           query.prepare("UPDATE MP SET REFERENCE =:ref ,DESCRIPTION=:desc, EMPLACEMENT=:emp, QUANTITE=:quan"
                         ",PRIX=:prix, DATE_ACHAT=:dateAchat, POIDS=:poids, VOLUME=:volume,COMMENTAIRE=:commentaire"
                         " WHERE REFERENCE =:ref");
           query.bindValue(":ref", reference);
           query.bindValue(":desc", description);
           query.bindValue(":emp", emplacement);
           query.bindValue(":quan", quantite);
           query.bindValue(":prix", prix);
           query.bindValue(":dateAchat", dateAchat);
           query.bindValue(":poids", poids);
           query.bindValue(":volume", volume);
           query.bindValue(":commentaire", commentaire);

           return query.exec();


 }







