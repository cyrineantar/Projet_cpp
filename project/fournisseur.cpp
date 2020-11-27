#include "fournisseur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
fournisseur::fournisseur()
{
    numero=0; rib=0; nom=""; matricule=""; produit=""; adresse=""; date="";
}

fournisseur::fournisseur(int numero,int rib,QString nom,QString matricule,QString produit,QString adresse,QString date)
{this->numero=numero; this->rib=rib; this->nom=nom;this->matricule=matricule;this->produit=produit;this->adresse=adresse;this->date=date;}
int fournisseur:: getnumero(){return numero;}
int fournisseur::getrib(){return rib;}
QString fournisseur:: getnom(){return nom;}
QString fournisseur:: getmatricule(){return matricule;}
QString fournisseur::getproduit(){return produit;}
QString fournisseur:: getadresse (){return adresse;}
QString fournisseur::getdate() {return date;}
void fournisseur::setnumero(int numero) {this->numero=numero;}
void fournisseur:: setrib(int rib) {this->rib=rib;}
void fournisseur:: setnom(QString nom) {this->nom=nom;}
void fournisseur:: setmatricule(QString matricule){this->matricule=matricule;}
void fournisseur:: setproduit(QString produit){this->produit=produit;}
void fournisseur:: setadresse(QString adresse){this->adresse= adresse;}
void fournisseur:: setdate(QString date){this->date=date;}
bool fournisseur::ajouter()
{

    QSqlQuery query;
  QString numero_string= QString::number(numero);
  QString rib_string=QString::number(rib);

  query.prepare("INSERT INTO fournisseur (numero,rib,nom,matricule,produit,adresse,date_ajout) "
                "VALUES (:numero,:rib,:nom,:matricule,:produit,:adresse,:date_ajout)");
  query.bindValue(":numero", numero_string);
  query.bindValue(":rib", rib_string);
  query.bindValue(":nom", nom);



  query.bindValue(":matricule",matricule);
  query.bindValue(":adresse", adresse);
  query.bindValue(":produit", produit);
  query.bindValue(":date", date);

        return query.exec();

}
bool fournisseur::supprimer(QString matricule)
{
    QSqlQuery query;
         query.prepare(" Delete from fournisseur where matricule=matricule");
         query.bindValue(0, matricule);

        return query.exec();


}
QSqlQueryModel* fournisseur::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM fournisseur");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Matricule"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Produit"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("Rib"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));


  return  model;
}
