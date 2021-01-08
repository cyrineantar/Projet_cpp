#ifndef ESPACE_FOURNISSEUR_H
#define ESPACE_FOURNISSEUR_H

#include <QDialog>
#include "fournisseur.h"
#include"achat.h"
#include  <QSound>
namespace Ui {
class Espace_fournisseur;
}

class Espace_fournisseur : public QDialog
{
    Q_OBJECT

public:
    explicit Espace_fournisseur(QWidget *parent = nullptr);
    ~Espace_fournisseur();
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


    void on_Excel_clicked();

private:
    Ui::Espace_fournisseur *ui;
    fournisseur f;
    achat a;
    QString fournisseurSelect;
    int achatselect;
     QSound *son;
};

#endif // ESPACE_FOURNISSEUR_H
