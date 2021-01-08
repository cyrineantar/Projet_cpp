#ifndef VENTE_H
#define VENTE_H
#include<QString>
#include <QString>
#include <QSqlQueryModel>


class vente
{
public:
    vente(int,QString,int,int,int,QString);
    void setnum_vente(int);
    void setprod(QString n);
    void setquant(int);
    void setid(int);
    void settot(int);
    void setdate_arr(QString n);
    int getnum_vente();
    QString getprod();
    int getquant();
    int getid();
    int gettot();
    QString getdate_arr();



    bool supprimer1(int);
    bool ajouter1();
    bool modifier1();
    bool supprimer1();
    QSqlQueryModel* afficher1();
    QSqlQueryModel* rechercher1(QString,QString);
    QSqlQueryModel* tri1(QString,QString);

    vente();

private:
    int num_vente,quant,id,tot;
    QString prod,date_arr;
};

#endif //VENTE_H
