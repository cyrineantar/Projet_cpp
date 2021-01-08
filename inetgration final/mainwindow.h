#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QSound>
#include "stock.h"
#include "espaceemploye.h"
#include "espace_fournisseur.h"
#include "espace_client.h"
#include "espace_machine.h"
#include "espace_livraison.h"



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
    void on_pushButton_clicked();

    void on_b_espaceE_clicked();

    void on_b_espaceF_clicked();

    void on_b_espaceC_clicked();

    void on_b_espaceM_clicked();

    void on_b_espaceL_clicked();

    void on_connexion_clicked();

    void on_Retour_menu_3_clicked();

    void on_b_espaceC_2_clicked();

    void on_pushButton_2_clicked();

    void on_b_espaceM_2_clicked();

    void on_b_espaceL_2_clicked();

    void on_pushButton_4_clicked();

    void on_b_espaceF_2_clicked();

private:

    Ui::MainWindow *ui;
    QSound *sonB;
    stock *s;
    espaceEmploye *e;
    Espace_fournisseur *f;
    Espace_client *c;
    espace_machine *b;
    Espace_livraison *l;



};
#endif // MAINWINDOW_H
