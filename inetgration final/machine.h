#ifndef MACHINE_H
#define MACHINE_H
#include<QString>
#include <QString>
#include <QSqlQueryModel>
#include <QMediaPlayer>


class machine
{
public:
    machine(QString,QString,QString,QString);
    void setcode(QString n);
    void setdate(QString n);
    void setfonctionnement(QString n);
    void setpuissance(QString n);

    QString get_code();
    QString get_date();
    QString get_fonctionnement();
    QString get_puissance();

    QSqlQueryModel* afficher();
    QSqlQueryModel* tri(QString,QString);
    bool supprimer(QString);
    bool ajouter();
    bool modifier(QString,QString, QString,QString);
    QSqlQueryModel* rechercher(QString,QString);
    machine();

private:
    QString code,date,fonctionnement,puissance,colone,ordre;

};

#endif // MACHINE_H
