#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "livraison.h"
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


   void on_Afficher_clicked();



   //void on_tableView_activated(const QModelIndex &index);

   //void on_tableView_doubleClicked(const QModelIndex &index);

   //void on_modifier_clicked();

   void on_le_recherche_textChanged(const QString &arg1);

   void on_supprimer_clicked();

   void on_modifier_2_clicked();

   void on_button_tri_clicked();

   void on_imprimer_clicked();

private:
   Ui::MainWindow *ui;
   livraison L  ;
};
#endif // MAINWINDOW_H
