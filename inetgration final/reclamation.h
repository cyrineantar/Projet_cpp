#ifndef RECLAMATION_H
#define RECLAMATION_H
#include<QString>
#include <QString>
#include <QSqlQueryModel>


class reclamation
{
public:
    reclamation();
    reclamation(QString,QString,QString);
    void setdate_panne(QString n);
    void setcause_panne(QString n);
    void setcodeM(QString n);
    QString get_date_panne();
    QString get_cause_panne();
    QString get_codeM();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool ajouter();
    bool modifier(QString,QString, QString);
    QSqlQueryModel* rechercher(QString,QString);
    QSqlQueryModel* tri(QString,QString);



private:
    QString date_panne,cause_panne,codeM;
};

#endif // RECLAMATION_H
