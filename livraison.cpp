#include "livraison.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

livraison::livraison()
{

    num_com=0;
    produit="";
    quantite=0;
    livreur="";
    total=0;
    date_arrivee="";

}

   livraison::livraison(int num_com,QString produit,int quantite,QString livreur, int total,QString date_arrivee)
{
   this->num_com =num_com;
   this->produit =produit;
   this->quantite =quantite;
   this->livreur =livreur;
   this->total =total;
   this->date_arrivee=date_arrivee;
}

   int livraison:: getnum_com(){return num_com;}
   QString livraison:: getproduit(){return produit;}
   int livraison::getquantite(){return quantite;}
   QString livraison:: getlivreur(){return livreur;}
   int livraison::gettotal(){return total;}
   QString livraison::getdate_arrivee(){return date_arrivee;}

   void livraison::setnum_com(int num_com) {this->num_com=num_com;}
   void livraison:: setproduit(QString produit) {this->produit=produit;}
   void livraison:: setquantite(int quantite) {this->quantite=quantite;}
   void livraison:: setlivreur(QString livreur){this->livreur=livreur;}
   void livraison:: settotal(int total){this->total=total;}
   void livraison:: setdate_arrivee(QString date_arrivee){this->date_arrivee= date_arrivee;}


   bool livraison::ajouter()
   {

       QSqlQuery query;


     query.prepare("INSERT INTO LIVRAISON (num_com,produit,quantite,livreur,total,date_arrivee) "
                   "VALUES (:num_com, :produit, :quantite, :livreur, :total, :date_arrivee)");
     query.bindValue(":num_com", num_com);
     query.bindValue(":produit", produit);
     query.bindValue(":quantite",quantite);
     query.bindValue(":livreur",livreur);
     query.bindValue(":total", total);
     query.bindValue(":date_arrivee", date_arrivee);

        return query.exec();

   }



   QSqlQueryModel* livraison::afficher()
   {
     QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT* FROM livraison");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero de commande"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Produit"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Livreur"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Total"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'arrivee"));



     return  model;
   }


   QSqlQueryModel* livraison::rechercher(QString colone,QString text)
   {
        QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM LIVRAISON WHERE UPPER("+colone+") LIKE UPPER('"+text+"%')");

        return model;
   }


   bool livraison::modifier()
   {
       QSqlQuery query;


            query.prepare("update livraison set produit=:produit, quantite=:quantite "
                          ",livreur=:livreur,total=:total,date_arrivee=:date_arrivee where num_com=:num_com");

            query.bindValue(":num_com", num_com);
            query.bindValue(":produit", produit);
            query.bindValue(":quantite",quantite);
            query.bindValue(":livreur",livreur);
            query.bindValue(":total",total);
            query.bindValue(":date_arrivee",date_arrivee);

           return query.exec();


   }

   bool livraison::supprimer()
   {
       QSqlQuery query;
               query.prepare("select * from livraison where num_com=:num_com");
               query.bindValue(":num_com", num_com);
               query.exec();
               if (query.next())
               {
                query.prepare(" Delete from livraison where num_com=:num_com");
                query.bindValue(":num_com", num_com);

                       query.exec();
                    return true;

               }

                return false;
   }

   QSqlQueryModel*  livraison::tri(QString colone, QString ordre)
   {
   QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("select * from livraison order by "+colone+" "+ordre+"");
   return model;
   }
