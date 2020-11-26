#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QtSql/QSqlQueryModel>

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
bool Employe::modifier(int ID,QString Nom,QString Prenom,QString Courriel,int Num_tel,QString Date_n,QString Adresse,QString Fonction,int Salaire,QString Etat_civil,QString Nationalite)
{
    QSqlQuery query;
    query.prepare("update EMPLOYE set Nom= '"+Nom+"' , Prenom= '"+Prenom+"', Courriel= '"+Courriel+"',Num_tel= '"+Num_tel+"',Date_n= '"+Date_n+"', Adresse= '"+Adresse+"',Fonction= '"+Fonction+"',Salaire= '"+Salaire+"' Etat_civil= '"+Etat_civil+"', Nationalite= '"+Nationalite+"' where ID= '"+ID+"' ");
          return query.exec();
}
