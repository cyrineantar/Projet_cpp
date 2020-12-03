#ifndef LIVRAISON_H
#define LIVRAISON_H
#include <QString>
#include <QSqlQueryModel>
class fournisseur
{public:
    fournisseur();
    fournisseur(int,int,QString,QString,QString,QString,QString);
    int getnumero();
    int getrib();
    QString getnom();
    QString getmatricule();
    QString getproduit();
    QString getadresse ();
    QString getdate() ;
    void setnumero(int);
    void setrib(int);
    void setnom(QString);
    void setmatricule(QString);
    void setproduit(QString);
    void setadresse(QString);
    void setdate(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    QSqlQueryModel* rechercher(QString,QString);
    QSqlQueryModel* tri(QString,QString);


private:
    int rib,numero;
    QString nom,matricule,produit,adresse,date;
};
#endif // ETUDIANT_H
