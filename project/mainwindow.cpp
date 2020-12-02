#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QIntValidator>
#include "achat.h"
#include <QSqlQuery>
#include<QSqlError>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_numero->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_rib->setValidator(new QIntValidator(0, 9999999, this));

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

    fournisseur f1;
    QMessageBox msgBox;
    if(f1.supprimer(fournisseurSelect))
       { msgBox.setText("Suppression avec succes.");
    ui->tabfournisseur->setModel(f.afficher());

    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();

}

void MainWindow::on_pb_ajoutercommande_clicked()
{
    int num_commande =ui->le_numcommande->text().toInt();
    int quantite=ui->le_quantite->text().toInt();
QString prix=ui->le_prix->text();
QString fournisseur=ui->le_fournisseur->text();
QString produit=ui->le_produitachat->text();
QString description=ui->le_adresse->text();
QString date=ui->le_dateachat->text();
achat a(num_commande,quantite,fournisseur,produit,date,prix,description);
 bool test=a.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tabachat->setModel(a.afficher());
 }
 else
     msgBox.setText("Echec d'ajout");
     msgBox.exec();

}

void MainWindow::on_tabfournisseur_activated()
{

      QSqlQuery query;
      query.prepare("SELECT * FROM FOURNISSEUR WHERE matricule=:val");
      query.bindValue(":val",fournisseurSelect);
      if (query.exec())
      {

          while(query.next())
          {
              ui->le_matricule_2->setText(query.value(0).toString());
              ui->le_adresse_2->setText(query.value(1).toString());
              ui->le_numero_2->setText(query.value(2).toString());
              ui->le_rib_2->setText(query.value(3).toString());
              ui->le_nom_2->setText(query.value(4).toString());
              ui->le_produit_2->setText(query.value(5).toString());
              ui->le_date_2->setText(query.value(6).toString());
          }

           }

          else {
                  QMessageBox::critical(this,tr("error::"), query.lastError().text());
          }

}

void MainWindow::on_pb_modifier_2_clicked()
{
    QString matricule, adresse, produit,nom, date;
        int rib,numero;
        matricule=ui->le_matricule_2->text();
        adresse=ui->le_adresse_2->text();
        numero=ui->le_numero_2->text().toInt();
        rib=ui->le_rib_2->text().toInt();
        nom=ui->le_nom_2->text();
        produit=ui->le_produit_2->text();
        date=ui->le_date_2->text();

        QString value;

        QSqlQuery query;
        query.prepare("UPDATE FOURNISSEUR SET   adresse='"+adresse+"',  numero=:numero,  rib=:rib,  nom='"+nom+"', produit='"+produit+"', date_ajout = '"+date+"' where matricule='"+matricule+"'");
        query.bindValue(":numero", numero);
        query.bindValue(":rib", rib);
        if (query.exec())
        {
            QMessageBox msgBox;
              msgBox.setText("Le Document a été modifié.");
              msgBox.exec();
         ui->tabfournisseur->setModel(f.afficher());
        }

        else
        {
            QMessageBox::critical(this,tr("error::"), query.lastError().text());
        }
}

void MainWindow::on_le_recherche_textChanged(const QString &arg1)
{
    fournisseur F;
       ui->tabfournisseur->setModel(F.rechercher(ui->cb_recherche->currentText(),arg1));
}

void MainWindow::on_tabfournisseur_clicked(const QModelIndex &index)
{
    fournisseurSelect=ui->tabfournisseur->model()->data(index.sibling(index.row(),0)).toString();

}

void MainWindow::on_pb_supprimer_2_clicked()
{
    achat a;
    achat a1;
    QMessageBox msgBox;
    if(a1.supprimer(achatselect))
       { msgBox.setText("Suppression avec succes.");
    ui->tabachat->setModel(a.afficher());

    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void MainWindow::on_le_recherche_2_textChanged(const QString &arg1)
{
    achat a;
       ui->tabachat->setModel(a.rechercher(ui->comboBox->currentText(),arg1));
}

void MainWindow::on_tabachat_clicked(const QModelIndex &index)
{
    achatselect=ui->tabachat->model()->data(index.sibling(index.row(),0)).toInt();

}

void MainWindow::on_pb_modifier_5_clicked()
{
    achat a;
    QString prix, description, fournisseur,date_achat, produit;
        int quantite,num_commande;
        num_commande=ui->le_numcommande_3->text().toInt();
        quantite=ui->le_quantite_3->text().toInt();
        prix=ui->le_prix_3->text();
        description=ui->le_description_3->text();
        fournisseur=ui->le_fournisseur_3->text();
        date_achat=ui->le_dateachat_3->text();
        produit=ui->le_produitachat_3->text();

        QString value;

        QSqlQuery query;
        query.prepare("UPDATE achat SET   prix='"+prix+"' ,  quantite=:quantite,  description='"+description+"', produit='"+produit+"', date_achat = '"+date_achat+"' where num_commande='"+num_commande+"'");
        query.bindValue(":num_commande", num_commande);
        query.bindValue(":quantite", quantite);
        if (query.exec())
        {
            QMessageBox msgBox;
              msgBox.setText("Le Document a été modifié.");
              msgBox.exec();
         ui->tabachat->setModel(a.afficher());
        }

        else
        {
            QMessageBox::critical(this,tr("error::"), query.lastError().text());
        }
}

void MainWindow::on_tabachat_activated()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM achat WHERE num_commande=:val");
    query.bindValue(":val",achatselect);
    if (query.exec())
    {

        while(query.next())
        {
            ui->le_numcommande_3->setText(query.value(0).toString());
            ui->le_quantite_3->setText(query.value(1).toString());
            ui->le_prix_3->setText(query.value(2).toString());
            ui->le_description_3->setText(query.value(3).toString());
            ui->le_fournisseur_3->setText(query.value(4).toString());
            ui->le_dateachat_3->setText(query.value(5).toString());
            ui->le_produitachat_3->setText(query.value(6).toString());
        }

         }

        else {
                QMessageBox::critical(this,tr("error::"), query.lastError().text());
        }

}
