#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QSqlQueryModel>
#include<QString>
class achat
{
public:
    achat();
    achat(int,int,QString,QString,QString,QString,QString);
    int getquantite();
    int getnum_commande();
    QString getprix();
    QString getdate_achat();
    QString getproduit();
    QString getdescription ();
    QString getfournisseur() ;
    void setquantite(int);
    void setnum_commande(int);
    void setprix(QString);
    void setproduit(QString);
    void setfournisseur(QString);
    void setdescription(QString);
    void setdate_achat(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel* rechercher(QString,QString);
    bool modifier();
    QSqlQueryModel* tri(QString,QString);



private:
    int num_commande,quantite;
    QString description,fournisseur,prix,produit,date_achat;
};

#endif // RECLAMATION_H
