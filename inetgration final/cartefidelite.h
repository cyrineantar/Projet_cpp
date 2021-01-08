#ifndef CARTEFIDELITE_H
#define CARTEFIDELITE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class CarteFidelite
{
public:
    CarteFidelite();
     CarteFidelite(int,QString,int,double,QString,int,QString);
     QSqlQueryModel * afficher();
     bool ajouter();
     bool modifier();
     bool supprimer();
     void setnumCarte(int numCarte){this->numCarte=numCarte;}


private:
    int numCarte;
    QString date_de_creation;
    int points;
    double totalAchats;
    QString statut;
    int remise;
    QString matriculeFiscale;

};

#endif // CARTEFIDELITE_H
