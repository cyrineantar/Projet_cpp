#ifndef CONGE_H
#define CONGE_H
#include<QString>
#include <QSqlQueryModel>

class conge
{
public:

    conge();
    conge(int,int,QString,QString,QString,QString);
       void setID_conge(int);
       void setID(int);
       void setDate_debut(QString m);
       void setDate_fin(QString m);
       void setMotif(QString m);
       void setType_conge(QString m);

       int get_ID_conge();
       int get_ID();
       void get_Date_debut(QString m);
       void get_Date_fin(QString m);
       void get_Motif(QString m);
       void get_Type_conge(QString m);

       bool ajouter_conge();
       QSqlQueryModel* afficher_conge();
       bool supprimer_conge(int);
       bool modifier_conge(int,int,QString,QString,QString,QString);
    ~conge(){}

private:
    QString Date_debut, Date_fin, Motif, Type_conge;
    int ID_conge,ID;
};

#endif // CONGE_H
