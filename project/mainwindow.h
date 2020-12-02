#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fournisseur.h"
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

private:
    Ui::MainWindow *ui;
    fournisseur f;

    QString fournisseurSelect;
    int achatselect;
};
#endif // MAINWINDOW_H
