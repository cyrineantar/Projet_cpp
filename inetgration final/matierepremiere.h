#ifndef MATIEREPREMIERE_H
#define MATIEREPREMIERE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class MatierePremiere
{
public:
    MatierePremiere();
    MatierePremiere(QString,QString,QString,int,double,QString,double,double,QString);
    bool ajouterMP();
    QSqlQueryModel* afficherMP();
    bool supprimerMP(QString Reference);
    bool modifierMP();
private:
    QString reference;
    QString description;
    QString emplacement;
    int quantite;
    double prix;
    QString dateAchat;
    double poids;
    double volume;
    QString commentaire;

};

#endif // MATIEREPREMIERE_H
