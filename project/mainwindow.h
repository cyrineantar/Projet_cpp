#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fournisseur.h"
#include"achat.h"
#include  <QSound>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{ Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_ajoutercommande_clicked();

    void on_tabfournisseur_activated();

    void on_pb_modifier_2_clicked();

    void on_le_recherche_textChanged(const QString &arg1);

    void on_tabfournisseur_clicked(const QModelIndex &index);

    void on_pb_supprimer_2_clicked();

    void on_le_recherche_2_textChanged(const QString &arg1);

    void on_tabachat_clicked(const QModelIndex &index);

    void on_pb_modifier_5_clicked();

    void on_tabachat_activated();

    void on_tri_clicked();

    void on_pushButton_clicked();


    void on_PDF_clicked();

    void on_tri_fournisseur_clicked();

    void on_imprimer_fournisseur_clicked();

    void on_pdf_clicked();

private:
    Ui::MainWindow *ui;
    fournisseur f;
    achat a;
    QString fournisseurSelect;
    int achatselect;
      QSound *son;
};
#endif // MAINWINDOW_H
