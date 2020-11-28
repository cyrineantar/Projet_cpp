#ifndef MACHINE_H
#define MACHINE_H
#include<QString>
#include <QString>
#include <QSqlQueryModel>


class machine
{
public:
    machine(QString,QString,QString,QString,QString);
    void setcode(QString n);
    void setdate(QString n);
    void settype(QString n);
    void setpuissance(QString n);
    void setconsommation(QString n);
    QString get_code();
    QString get_date();
    QString get_type();
    QString get_puissance();
    QString get_consommation();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool ajouter();
    machine();

private:
    QString code,date,type,puissance,consommation;
};

#endif // MACHINE_H
