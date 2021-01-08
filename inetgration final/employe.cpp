#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QtSql/QSqlQueryModel>
#include <QMessageBox>
#include <QMediaPlayer>

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
        QString ID_string=QString::number(ID);
        QString Num_tel_string=QString::number(Num_tel);
        QString Salaire_string=QString::number(Salaire);

              query.prepare("UPDATE EMPLOYE SET ID=:id, NOM=:Nom, PRENOM=:Prenom, COURRIEL=:Courriel,"
                            "NUM_TEL=:Num_tel, DATE_N=:Date_n, ADRESSE=:Adresse, FONCTION=:Fonction,"
                            "SALAIRE=:Salaire, ETAT_CIVIL=:Etat_civil, NATIONALITE=:Nationalite"
                            "WHERE ID=:id");
              query.bindValue(":id",ID_string);
              query.bindValue(":Nom",Nom);
              query.bindValue(":Prenom",Prenom);
              query.bindValue(":Courriel",Courriel);
              query.bindValue(":Num_tel",Num_tel_string);
              query.bindValue(":Date_n",Date_n);
              query.bindValue(":Adresse",Adresse);
              query.bindValue(":Fonction",Fonction);
              query.bindValue(":Salaire",Salaire_string);
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
QSqlQueryModel* Employe::tri_ID()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM EMPLOYE ORDER BY ID ASC");

    return model;
}

QSqlQueryModel* Employe::tri_nom()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM EMPLOYE ORDER BY NOM ASC");

    return model;
}

QSqlQueryModel* Employe::tri_prenom()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM EMPLOYE ORDER BY PRENOM ASC");

    return model;
}
bool Employe::recherche_prenom(QString Prenom)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE PRENOM= :prenom");
    query.bindValue(":prenom", Prenom);
    if (query.exec() && query.next())
    {
            return true;

    }
    else
    {

        msgBox.setText("Non existant");
        msgBox.exec();
        return false;
    }
}
bool Employe::recherche_nom(QString Nom)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE NOM= :nom");
    query.bindValue(":nom", Nom);
    if (query.exec() && query.next())
    {
            return true;

    }
    else
    {

        msgBox.setText("Non existant");
        msgBox.exec();
        return false;
    }
}
bool Employe::recherche_adresse(QString Adresse)
{

    QMessageBox msgBox;
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE ADRESSE= :adresse");
    query.bindValue(":adresse", Adresse);
    if (query.exec() && query.next())
    {
            return true;

    }
    else
    {

        msgBox.setText("Non existant");
        msgBox.exec();
        return false;
    }
}
QSqlQueryModel* Employe::afficher_nom(QString nom)
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM EMPLOYE WHERE NOM='"+nom+"'");

    return model;
}
QSqlQueryModel* Employe::afficher_prenom(QString prenom)
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM EMPLOYE WHERE PRENOM='"+prenom+"'");

    return model;
}
QSqlQueryModel* Employe::afficher_adresse(QString adresse)
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM EMPLOYE WHERE ADRESSE=:'"+adresse+"");

    return model;
}


