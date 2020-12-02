#include "achat.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
achat::achat()
{
    quantite=0; num_commande=0; date_achat=""; produit=""; fournisseur=""; description=""; prix="";
}

achat::achat(int num_commande,int quantite,QString date,QString produit,QString description,QString prix,QString fournisseur)
{this->num_commande=num_commande; this->quantite=quantite; this->date_achat=date;this->produit=produit;this->description=description;this->prix=prix;this->fournisseur=fournisseur;}
int achat:: getnum_commande(){return num_commande;}
int achat::getquantite(){return quantite;}
QString achat:: getprix(){return prix;}
QString achat:: getdescription(){return description;}
QString achat::getproduit(){return produit;}
QString achat:: getfournisseur (){return fournisseur;}
QString achat::getdate() {return date_achat;}
void achat:: setnum_commande(int num_commande) {this->num_commande=num_commande;}
void achat:: setquantite(int quantite) {this->quantite=quantite;}
void achat:: setprix(QString prix) {this->prix=prix;}
void achat:: setfournisseur(QString fournisseur){this->fournisseur=fournisseur;}
void achat:: setproduit(QString produit){this->produit=produit;}
void achat:: setdescription(QString description){this->description= description;}
void achat:: setdate(QString date){this->date_achat=date;}
bool achat::ajouter()
{

    QSqlQuery query;
  QString num_commande_string= QString::number(num_commande);
  QString quantite_string=QString::number(quantite);

  query.prepare("INSERT INTO ACHAT (num_commande"
                ",quantite,prix,description,fournisseur,date_achat,produit) "
                "VALUES (:num_commande,:quantite,:prix,:description,:fournisseur,:date_achat,:produit)");
  query.bindValue(":num_commande", num_commande_string);
  query.bindValue(":quantite", quantite_string);
  query.bindValue(":fournisseur", fournisseur);
  query.bindValue(":description",description);
  query.bindValue(":prix", prix);
  query.bindValue(":produit", produit);
  query.bindValue(":date", date_achat);

        return query.exec();

}
bool achat::supprimer(int num_commande)
{
    QSqlQuery query;
    query.prepare("select * from achat where num_commande=:num_commande");
    query.bindValue(0, num_commande);
    query.exec();
    if (query.next())
    {
     query.prepare(" Delete from achat where num_commande=:num_commande");
     query.bindValue(0, num_commande);

            query.exec();
         return true;

    }

     return false;


}
QSqlQueryModel* achat::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM ACHAT");


  return  model;
}
QSqlQueryModel* achat::rechercher(QString colone,QString text)
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FOURNISSEUR WHERE UPPER("+colone+") LIKE UPPER('"+text+"%')");

     return model;
}

