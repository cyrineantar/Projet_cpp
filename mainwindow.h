#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
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

private:
   Ui::MainWindow *ui;
   Employe E;
};
#endif // MAINWINDOW_H

