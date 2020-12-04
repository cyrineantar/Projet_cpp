#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include <QSqlQueryModel>

class Employe
{
public:

    Employe();
    Employe(int,QString,QString,QString,int,QString,QString,QString,int,QString,QString);
    void setID(int);
       void setNom(QString n);
       void setPrenom(QString n);
       void setCourriel(QString n);
       void setNum_tel(int);
       void setDate_n(QString n);
       void setAdresse(QString n);
       void setFonction(QString n);
       void setSalaire(int);
       void setEtat_civil(QString n);
       void setNationalite(QString n);

       int get_ID();
       QString get_Nom();
       QString get_Prenom();
       QString get_Courriel();
       int get_Num_tel();
       QString get_Date_n();
       QString get_Adresse();
       QString get_Fonction();
       int get_Salaire();
       QString get_Etat_civil();
       QString get_Nationalite();
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,int,QString,QString,QString,int,QString,QString);
    QSqlQueryModel* rechercher(int,QString,QString);
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_prenom();
    QSqlQueryModel* tri_ID();
    bool recherche_prenom(QString prenom);
    bool recherche_nom(QString Nom);
    bool recherche_Fonction(QString Fonction);
    QSqlQueryModel* afficher_nom(QString nom);
    QSqlQueryModel* afficher_prenom(QString prenom);
    QSqlQueryModel* afficher_Fonction(QString Fonction);

    ~Employe(){}

private:
    QString Nom, Prenom, Courriel, Date_n, Adresse, Fonction, Etat_civil, Nationalite;
    int ID, Num_tel, Salaire;
};


#endif // EMPLOYE_H
