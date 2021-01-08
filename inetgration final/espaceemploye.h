#ifndef ESPACEEMPLOYE_H
#define ESPACEEMPLOYE_H

#include "employe.h"
#include "conge.h"
#include <QTableView>
#include <QComboBox>
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QSound>
#include <QDialog>
#include"chat_employe.h"
#include"chat_server.h"

namespace Ui {
class espaceEmploye;
}

class espaceEmploye : public QDialog
{
    Q_OBJECT

public:
    explicit espaceEmploye(QWidget *parent = nullptr);
    ~espaceEmploye();

private slots:

   void on_Ajouter_clicked();

   void on_Supprimer_clicked();

   void on_Modifier_clicked();

   void on_tableView_clicked(const QModelIndex &index);

   void on_Rechercher_clicked();

   void on_Tri_clicked();

   void on_Pdf_clicked();

   void on_Imprimer_clicked();

   void on_Quitter_clicked();

   void on_Ajouter_conge_clicked();

   void on_tableView_2_clicked(const QModelIndex &index);

   void remplir_cb_employID();

   void on_Supprimer_conge_clicked();

   void on_Tri_conge_clicked();

   void on_Modifier_conge_clicked();


   void on_Pdf_conge_clicked();

   void on_Imprimer_conge_clicked();

   void on_Quitter_2_clicked();

   void on_Rechercher_conge_clicked();
   void on_b_chat_2_clicked();

private:
    Ui::espaceEmploye *ui;
    Employe E;
    conge C;
    QRegExp MRE ;
    QSound *clickSound;

};

#endif // ESPACEEMPLOYE_H
