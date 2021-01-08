#ifndef ESPACE_LIVRAISON_H
#define ESPACE_LIVRAISON_H

#include <QDialog>
#include <QObject>
#include "livraison.h"
#include "vente.h"
#include  <QSound>
#include "arduino.h"
namespace Ui {
class Espace_livraison;
}

class Espace_livraison : public QDialog
{
    Q_OBJECT

public:
    explicit Espace_livraison(QWidget *parent = nullptr);
    ~Espace_livraison();
private slots:

   void on_Ajouter_clicked();


  // void on_Afficher_clicked();



   //void on_tableView_activated(const QModelIndex &index);

   //void on_tableView_doubleClicked(const QModelIndex &index);

   //void on_modifier_clicked();

   void on_le_recherche_textChanged(const QString &arg1);

   void on_supprimer_clicked();

   void on_modifier_2_clicked();

   void on_button_tri_clicked();

   void on_imprimer_clicked();

   void on_PDF_clicked();

   void on_tabWidget_2_tabBarClicked(int index);

   void on_ajouter1_clicked();

   void on_affichage2_tabBarClicked(int index);

   void on_le_recherche_2_textChanged(const QString &arg1);

   void on_button_tri_2_clicked();

   void on_supprimer_2_clicked();

   void on_imprimer_2_clicked();

   void on_PDF_2_clicked();

   void on_modifier3_clicked();

private:
    Ui::Espace_livraison *ui;
    QSound *son;
    QByteArray data;
    Arduino A;

};

#endif // ESPACE_LIVRAISON_H
