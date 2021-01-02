#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "livraison.h"
#include "vente.h"
#include  <QSound>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

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

   void on_cb_recherche_2_editTextChanged(const QString &arg1);

private:
   Ui::MainWindow *ui;
   livraison L ;
   vente v;
   QSound *son;
};
#endif // MAINWINDOW_H
