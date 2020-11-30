#include "conge.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QtSql/QSqlQueryModel>

conge::conge()
{
    ID_conge=0;
    ID=1;
    Date_debut="";
    Date_fin="";
    Motif="";
    Type_conge="";
}

conge::conge(int ID_conge, int ID, QString Date_debut, QString Date_fin, QString Motif, QString Type_conge)
{
    this->ID_conge=ID_conge;
    this->ID=ID;
    this->Date_debut=Date_debut;
    this->Date_fin=Date_fin;
    this->Motif=Motif;
    this->Type_conge=Type_conge;

}
void conge::setID_conge(int ID_conge){this->ID_conge=ID_conge;}

int conge::get_ID_conge(){return ID_conge;}

bool conge::ajouter_conge()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CONGE(ID_conge, ID, Date_debut, Date_fin, Motif, Type_conge)"
                  "VALUES (:ID_conge, :ID, :Date_debut, :Date_fin, :Motif, :Type_conge)");
    query.bindValue(":ID_conge",ID_conge);
    query.bindValue(":ID",ID);
    query.bindValue(":Date_debut",Date_debut);
    query.bindValue(":Date_fin",Date_fin);
    query.bindValue(":Motif",Motif);
    query.bindValue(":Type_conge",Type_conge);


    return query.exec();
}

QSqlQueryModel* conge::afficher_conge()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM CONGE");

    return model;
}
