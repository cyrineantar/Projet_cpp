#include "vente.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

vente::vente()
{

    num_vente=0;
    prod="";
    quant=0;
    id=0;
    tot=0;
    date_arr="";

}

   vente::vente(int num_vente,QString prod,int quant,int id, int tot,QString date_arr)
{
   this->num_vente=num_vente;
   this->prod=prod;
   this->quant=quant;
   this->id=id;
   this->tot=tot;
   this->date_arr=date_arr;
}

   int vente:: getnum_vente(){return num_vente;}
   QString vente::getprod(){return prod;}
   int vente::getquant(){return quant;}
   int vente:: getid(){return id;}
   int vente::gettot(){return tot;}
   QString vente::getdate_arr(){return date_arr;}

   void vente:: setnum_vente(int num_vente) {this->num_vente=num_vente;}
   void vente:: setprod(QString prod) {this->prod=prod;}
   void vente:: setquant(int quant) {this->quant=quant;}
   void vente:: setid(int id){this->id=id;}
   void vente:: settot(int tot){this->tot=tot;}
   void vente:: setdate_arr(QString date_arr){this->date_arr=date_arr;}


   bool vente::ajouter1()
   {

       QSqlQuery query;


     query.prepare("INSERT INTO VENTE (num_vente,prod,quant,id,tot,date_arr) "
                   "VALUES (:num_vente,:prod,:quant,:id,:tot,:date_arr)");
     query.bindValue(":num_vente", num_vente);
     query.bindValue(":prod",prod);
     query.bindValue(":quant",quant);
     query.bindValue(":id",id);
     query.bindValue(":tot",tot);
     query.bindValue(":date_arr",date_arr);

        return query.exec();

   }



   QSqlQueryModel* vente::afficher1()
   {
     QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT* FROM vente");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("num_vente"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("prod"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("quant"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("id"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("tot"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_arr"));



     return  model;
   }


   QSqlQueryModel* vente::rechercher1(QString colone,QString text)
   {
        QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM VENTE WHERE UPPER("+colone+") LIKE UPPER('"+text+"%')");

        return model;
   }



   bool vente::modifier1()
   {
       QSqlQuery query;


            query.prepare("update vente set prod=:prod, quant=:quant "
                          ",id=:id,tot=:tot,date_arr=:date_arr where num_vente=:num_vente");

            query.bindValue(":num_vente",num_vente);
            query.bindValue(":prod", prod);
            query.bindValue(":quant",quant);
            query.bindValue(":id",id);
            query.bindValue(":tot",tot);
            query.bindValue(":date_arr",date_arr);

           return query.exec();


   }

   bool vente::supprimer1()
   {
       QSqlQuery query;
               query.prepare("select * from vente where num_vente=:num_vente");
               query.bindValue(":num_vente", num_vente);
               query.exec();
               if (query.next())
               {
                query.prepare(" Delete from vente where num_vente=:num_vente");
                query.bindValue(":num_vente", num_vente);

                       query.exec();
                    return true;

               }

                return false;
   }



   QSqlQueryModel*  vente::tri1(QString colone, QString ordre)
   {
   QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("select * from vente order by "+colone+" "+ordre+"");
   return model;
   }




