#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "livraison.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include <iostream>
#include <QDebug>
#include <QRadioButton>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QtPrintSupport/QPrintDialog>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->num_com->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(L.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ajouter_clicked()
{
      int num_com=ui->num_com->text().toInt();
      QString produit=ui->produit->text();
      int quantite=ui->quantite->text().toInt();
      QString livreur=ui->livreur->text();
      int total=ui->total->text().toInt();
      QString date_arrivee=ui->date_arrivee->text();

livraison L(num_com,produit,quantite,livreur,total,date_arrivee);

 bool test=L.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tableView->setModel(L.afficher());
   }
 else
{
     msgBox.setText("Echec d'ajout");
     msgBox.exec();

}
}





/*void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

        QString val =ui->tableView->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM LIVRAISON WHERE num_com='"+val+"' or produit='"+val+"' or quantite='"+val+"' or livreur='"+val+"' or total='"+val+"'or date_arrivee='"+val+"'");
        if (query.exec())
        {

            while(query.next())
            {
                ui->num_com_modif->setText(query.value(0).toString());
                ui->produit_modif->setText(query.value(1).toString());
                ui->quantite_modif->setText(query.value(2).toString());
                ui->livreur_modif->setText(query.value(3).toString());
                ui->total_modif->setText(query.value(4).toString());
                ui->date_modif->setText(query.value(5).toString());

            }

             }

            else {
                    QMessageBox::critical(this,tr("error::"), query.lastError().text());
            }

    }
*/

/*void MainWindow::on_modifier_clicked()
{
     int num_com,quantite,total;
    QString produit,livreur,date_arrivee;

       num_com=ui->num_com_modif->text().toInt();
       produit=ui->produit_modif->text();
       quantite=ui->quantite_modif->text().toInt();
       livreur=ui->livreur_modif->text();
       total=ui->total_modif->text().toInt();
       date_arrivee=ui->date_modif->text();

       QString value;

       QSqlQuery query;
       query.prepare("UPDATE LIVRAISON SET num_com='"+num_com+"',  produit='"+produit+"',  quantite='"+quantite+"',  livreur='"+livreur+"',  total='"+ total+"',  date_arrivee='"+ date_arrivee+"'");

       if (query.exec())
       {
           QMessageBox msgBox;
             msgBox.setText("Le Document a été modifié.");
             msgBox.exec();
        ui->tableView->setModel(L.afficher());

       }

       else
       {
           QMessageBox::critical(this,tr("error::"), query.lastError().text());
       }
}
*/
void MainWindow::on_le_recherche_textChanged(const QString &arg1)
{
    livraison L;
        ui->tableView->setModel(L.rechercher(ui->cb_recherche->currentText(),arg1));
}

/*void MainWindow::on_tableView_activated(const QModelIndex &index)
{

}*/

void MainWindow::on_supprimer_clicked()
{
    int num_com =ui->le_supprimer->text().toInt();
         livraison L;
         L.setnum_com(num_com);
         QMessageBox msg;
         if(L.supprimer())
         {
             msg.setText("suppression avec succés");
             ui->tableView->setModel(L.afficher());

         }
         else
         {
             msg.setText("echec de suppression");
         }
         msg.exec();
}

void MainWindow::on_modifier_2_clicked()
{
    int num_com,quantite,total;
   QString produit,livreur,date_arrivee;

   num_com=ui->num_com_2->text().toInt();
   produit=ui->produit_2->text();
   quantite=ui->quantite_2->text().toInt();
   livreur=ui->livreur_2->text();
   total=ui->total_2->text().toInt();
   date_arrivee=ui->date_arrivee_2->text();

   livraison L(num_com,produit,quantite,livreur,total,date_arrivee);

   QMessageBox msgBox;
       if (L.modifier())
       {

             msgBox.setText("Le Document a été modifié.");

             ui->tableView->setModel(L.afficher());

       }

       else
       {
           msgBox.setText("échec de modification.");
       }
       msgBox.exec();

}

void MainWindow::on_button_tri_clicked()
{
    QString colone=ui->colone_tri->currentText();
        QString ordre=ui->ordre_tri->currentText();
        livraison L;
        ui->tableView->setModel(L.tri(colone,ordre));
}

void MainWindow::on_imprimer_clicked()
{
    QPrinter printer;
                QPrintDialog *printDialog = new QPrintDialog(&printer, this);
                printDialog->setWindowTitle("Imprimer Document");
                printDialog->exec();
}
