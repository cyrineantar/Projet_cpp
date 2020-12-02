#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "produit.h"
#include <QTableView>
#include <QComboBox>
#include "matierepremiere.h"

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
    void on_Button_Ajouter_clicked();

    void on_Button_Supprimer_clicked();

    void on_tabProduits_activated();

    void on_le_rechercheP_textChanged();

    void show_tables(QSqlQueryModel*,QTableView *);

    void recherche(QSqlQueryModel*,QTableView *,QComboBox * ,QLineEdit * );

    void on_tabProduits_clicked(const QModelIndex &index);

    void on_button_okAjout_accepted();

    void on_button_okAjout_rejected();

    void on_button_okModif_accepted();

    void on_button_okModif_rejected();

    void on_Button_exporterExcel_clicked();

    void on_cb_champ_currentIndexChanged(int index);


    void on_button_okAjoutMP_accepted();

    void on_button_okAjoutMP_rejected();

    void on_le_rechercheMP_textChanged();

    void on_Button_AjouterMP_clicked();

    void on_Button_SupprimerMP_clicked();

    void on_tabMP_clicked(const QModelIndex &index);

    void on_tabMP_activated();

    void on_button_okAjoutMP_2_accepted();

    void on_button_okAjoutMP_2_rejected();

    void on_Button_ExportMP_clicked();

    void on_le_rechercheMP_affecter_textChanged();

    void on_cb_coloneR_affectMP_currentIndexChanged(int index);

    void on_tab_affectMP_activated(const QModelIndex &index);

    void remplir_champsModifP();
    void remplir_champsModifMP();
    void on_tab_ref_mpAffecte_clicked(const QModelIndex &index);

    void on_Button_desaffecterMP_clicked();

private:

    Ui::MainWindow *ui;
    Produit p;
    MatierePremiere mp;
    QSortFilterProxyModel *proxy;
    QString produitSelectionne;
    QString mpSelectionne;
    QVector <QString> mp_a_affecte;
    QVector <int> num_row_mpAffecte;
    QString mpAffecte_selectionne;


};
#endif // MAINWINDOW_H
