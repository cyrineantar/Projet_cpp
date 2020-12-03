#include "achat.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
achat::achat()
{
    quantite=0; num_commande=0; date_achat=""; produit=""; fournisseur=""; description=""; prix="";
}

achat::achat(int num_commande,int quantite,QString prix,QString description,QString fournisseur,QString date_achat,QString produit)
{this->num_commande=num_commande; this->quantite=quantite;this->prix=prix;this->description=description;this->fournisseur=fournisseur; this->date_achat=date_achat;this->produit=produit;}
int achat:: getnum_commande(){return num_commande;}
int achat::getquantite(){return quantite;}
QString achat:: getprix(){return prix;}
QString achat:: getdescription(){return description;}
QString achat:: getfournisseur (){return fournisseur;}
QString achat::getdate_achat() {return date_achat;}
QString achat::getproduit(){return produit;}

void achat:: setnum_commande(int num_commande) {this->num_commande=num_commande;}
void achat:: setquantite(int quantite) {this->quantite=quantite;}
void achat:: setprix(QString prix) {this->prix=prix;}
void achat:: setdescription(QString description){this->description= description;}
void achat:: setfournisseur(QString fournisseur){this->fournisseur=fournisseur;}
void achat:: setdate_achat(QString date_achat){this->date_achat=date_achat;}
void achat:: setproduit(QString produit){this->produit=produit;}



bool achat::ajouter()
{

    QSqlQuery query;
  QString num_commande_string= QString::number(num_commande);
  QString quantite_string=QString::number(quantite);

  query.prepare("INSERT INTO ACHAT (num_commande,quantite,prix,description,fournisseur,date_achat,produit) "
                "VALUES (:num_commande,:quantite,:prix,:description,:fournisseur,:date_achat,:produit)");
  query.bindValue(":num_commande", num_commande_string);
  query.bindValue(":quantite", quantite_string);
  query.bindValue(":prix", prix);
  query.bindValue(":description",description);
  query.bindValue(":fournisseur", fournisseur);
  query.bindValue(":date_achat", date_achat);
  query.bindValue(":produit", produit);

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


   model->setQuery("SELECT* FROM achat");

      model->setHeaderData(1, Qt::Vertical, QObject::tr("num_commande"));
      model->setHeaderData(2, Qt::Vertical, QObject::tr("quantite"));
      model->setHeaderData(3, Qt::Vertical, QObject::tr("prix"));
      model->setHeaderData(4, Qt::Vertical, QObject::tr("description"));
      model->setHeaderData(5, Qt::Vertical, QObject::tr("fournisseur"));
      model->setHeaderData(6, Qt::Vertical, QObject::tr("date_achat"));
      model->setHeaderData(7, Qt::Vertical, QObject::tr("produit"));

  return  model;
}
QSqlQueryModel* achat::rechercher(QString colone,QString text)
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM achat WHERE UPPER("+colone+") LIKE UPPER('"+text+"%')");

     return model;
}


bool achat::modifier()
{
    QSqlQuery query;


         query.prepare("update achat set  quantite=:quantite "
                       ",prix=:prix,description=:description ,fournisseur=:fournisseur ,date_achat=:date_achat ,produit=:produit where num_commande=:num_commande");

         query.bindValue(":num_commande", num_commande);
         query.bindValue(":quantite", quantite);
         query.bindValue(":prix",prix);
         query.bindValue(":description",description);
         query.bindValue(":fournisseur",fournisseur);
         query.bindValue(":date_achat",date_achat);
         query.bindValue(":produit",produit);


        return query.exec();


}

QSqlQueryModel*  achat::tri(QString colone, QString ordre)
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("select * from achat order by "+colone+" "+ordre+"");
return model;
}
