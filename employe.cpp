#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QtSql/QSqlQueryModel>
#include <QMessageBox>

Employe::Employe()
{
    ID=0;
    Nom="";
    Prenom="";
    Courriel="";
    Num_tel=1;
    Date_n="";
    Adresse="";
    Fonction="";
    Salaire=2;
    Etat_civil="";
    Nationalite="";
}

Employe::Employe(int ID,QString Nom,QString Prenom,QString Courriel,int Num_tel,QString Date_n,QString Adresse,QString Fonction,int Salaire,QString Etat_civil,QString Nationalite)
{
    this->ID=ID;
    this->Nom=Nom;
    this->Prenom=Prenom;
    this->Courriel=Courriel;
    this->Num_tel=Num_tel;
    this->Date_n=Date_n;
    this->Adresse=Adresse;
    this->Fonction=Fonction;
    this->Salaire=Salaire;
    this->Etat_civil=Etat_civil;
    this->Nationalite=Nationalite;
}
void Employe::setID(int ID){this->ID=ID;}

int Employe::get_ID(){return ID;}

bool Employe::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE(ID, Nom, Prenom,Courriel,Num_tel,Date_n,Adresse,Fonction,Salaire,Etat_civil,Nationalite)"
                  "VALUES (:ID, :Nom, :Prenom, :Courriel, :Num_tel, :Date_n, :Adresse, :Fonction, :Salaire, :Etat_civil, :Nationalite)");
    query.bindValue(":ID",ID);
    query.bindValue(":Nom",Nom);
    query.bindValue(":Prenom",Prenom);
    query.bindValue(":Courriel",Courriel);
    query.bindValue(":Num_tel",Num_tel);
    query.bindValue(":Date_n",Date_n);
    query.bindValue(":Adresse",Adresse);
    query.bindValue(":Fonction",Fonction);
    query.bindValue(":Salaire",Salaire);
    query.bindValue(":Etat_civil",Etat_civil);
    query.bindValue(":Nationalite",Nationalite);

    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM EMPLOYE");

    return model;
}
bool Employe::supprimer(int ID)
{
    QSqlQuery query;
    query.prepare("Delete from EMPLOYE where ID=:ID");
    query.bindValue(0,ID);

    return query.exec();
}
bool Employe::modifier(int,QString,QString,QString,int,QString,QString,QString,int,QString,QString)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET  ID =:id, NOM=:Nom, PRENOM =:Prenom, COURRIEL=:Courriel,NUM_TEL=:Num_tel, DATE_N =:Date_n, ADRESSE=:Adresse, FONCTION=:Fonction, SALAIRE=:Salaire, ETAT_CIVIL=:Etat_civil, NATIONALITE=:Nationalite where ID=:id");

    query.bindValue(":id",ID);
    query.bindValue(":Nom",Nom);
    query.bindValue(":Prenom",Prenom);
    query.bindValue(":Courriel",Courriel);
    query.bindValue(":Num_tel",Num_tel);
    query.bindValue(":Date_n",Date_n);
    query.bindValue(":Adresse",Adresse);
    query.bindValue(":Fonction",Fonction);
    query.bindValue(":Salaire",Salaire);
    query.bindValue(":Etat_civil",Etat_civil);
    query.bindValue(":Nationalite",Nationalite);
return query.exec();
}

QSqlQueryModel * Employe::rechercher(int ID, QString Nom, QString Prenom)
   {

       QMessageBox msgBox;
       QMessageBox msgBox1;

       QSqlQueryModel *model = new QSqlQueryModel;
       QSqlQuery query;
       int count=0;


       model->setQuery("SELECT * FROM EMPLOYE WHERE ID= ? and Nom= ? and Prenom= ?");
       query.addBindValue(ID);
       query.addBindValue(Nom);
       query.addBindValue(Prenom);



       if(query.exec() )

       {
   while (query.next())
      {
      count ++;
   }
   if(count==1)
      {
       msgBox.setText("Employe existe");
       msgBox.exec();
       model->setQuery(query);
   }

   else if (count<1)
   {
       msgBox1.setText("Employe n'existe pas");
           msgBox1.exec();
           model=0;
   }

       }



       return model;


   }

