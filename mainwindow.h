#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "conge.h"
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

private:
   Ui::MainWindow *ui;
   Employe E;
   conge C;

};
#endif // MAINWINDOW_H

