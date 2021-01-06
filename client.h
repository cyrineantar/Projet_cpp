#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{
public:
    Client();
    Client(QString,QString,QString,QString,QString,QString,int,QString,QString);
    //setters
    void setnomEntreprise(QString nom){nomEntreprise=nom;}
    void setdescription(QString des){description=des;}
    void setEmail(QString mail){Email=mail;}
    void setadresse(QString adresse){this->adresse=adresse;}
    void setville(QString ville){this->ville=ville;}
    void setcodePostal(int codePostal){this->codePostal=codePostal;}
    void setnumTel(QString numTel){this->numTel=numTel;}
    void setnumFax(QString numFax){this->numFax=numFax;}
    //getters
    QString getnomEntreprise(){return nomEntreprise;}
    QString getdescription(){return description;}
    QString getmatriculeFiscale(){return matriculeFiscale;}
    QString getEmail(){return Email;}
    QString getadresse(){return adresse;}
    QString getville(){return ville;}
    int getcodePostal(){return  codePostal;}
    QString getnumTel(){return numTel;}
    QString getnumFax(){return numFax;}
    //CRUD
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(QString mf_produitSelectionne);




private:
    QString nomEntreprise;
    QString description;
    QString matriculeFiscale;
    QString Email;
    QString adresse;
    QString ville;
    int codePostal;
    QString numTel;
    QString numFax;


};

#endif // CLIENT_H
