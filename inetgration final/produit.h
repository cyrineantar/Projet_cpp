#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Produit
{
public:

    Produit();
    Produit(int,double,double,double,double,QString,QString,QString,QString,QString,QString,QString);
    //functions
    bool ajouterProduit();
    QSqlQueryModel* afficherProduit();
    bool supprimerProduit(QString Reference);
    bool modifierProduit();
    bool affecterMP(QString RefMP);
    QSqlQueryModel* afficher_MPaffecte();
    bool suppAffectation(QString);
    void setReference(QString Reference){this->Reference=Reference;}

private:
    int Quantite;
    double Prix;
    double Dimensions;
    double Poids;
    double Volume;
    QString Categorie;
    QString Description;
    QString Reference;
    QString Emplacement;
    QString Date_de_creation;
    QString Date_d_expiration;
    QString Commentaire;


};

#endif // PRODUIT_H
