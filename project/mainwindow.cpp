#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_numero->setValidator(new QIntValidator(0, 9999999, this));
ui->tabfournisseur->setModel(f.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int numero=ui->le_numero->text().toInt();
int rib=ui->le_rib->text().toInt();
QString nom=ui->le_nom->text();
QString matricule=ui->le_matricule->text();
QString produit=ui->le_produit->text();
QString adresse=ui->le_adresse->text();
QString date=ui->le_date->text();
fournisseur f(numero,rib,nom,matricule,produit,adresse,date);
 bool test=f.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tabfournisseur->setModel(f.afficher());
 }
 else
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}

void MainWindow::on_pb_supprimer_clicked()
{
    fournisseur f1; f1.setmatricule(ui->le_matricule_supp->text());
    bool test=f1.supprimer(f1.getmatricule());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tabfournisseur->setModel(f.afficher());

    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();

}
