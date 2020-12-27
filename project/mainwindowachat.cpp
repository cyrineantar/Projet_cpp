#include "mainwindowachat.h"
#include "ui_mainwindowachat.h"
#include <QMessageBox>
#include <QIntValidator>
#include "achat.h"
#include<QDebug>
#include<QMessageBox>
#include<QIntValidator>
#include<QLabel>
#include<QSqlQuery>
#include<QSqlError>
#include <QModelIndex>
#include <QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include<QDesktopServices>
#include <QMessageBox>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include<QSound>

MainWindowAchat::MainWindowAchat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowAchat)
{
    ui->setupUi(this);
     son=new QSound(":/son/click.wav");
     ui->tabachat->setModel(a.afficher());
     QSqlQuery query;
             query.prepare("SELECT NOM FROM FOURNISSEUR");
             if(query.exec())
             {

                     while(query.next())
                     {
                         ui->combo_fournisseur->addItem(query.value(0).toString());
                     }
             }

                     query.prepare("SELECT nom FROM fournisseur");
                     if(query.exec())
                     {

                             while(query.next())
                             {
                                 ui->combo_fournisseur_2->addItem(query.value(0).toString());
                             }
                     }

}

MainWindowAchat::~MainWindowAchat()
{
    delete ui;
}

void MainWindowAchat::on_pb_ajoutercommande_clicked()
{
    son->play();
       int num_commande =ui->le_numcommande->text().toInt();
       int quantite=ui->le_quantite->text().toInt();
   QString prix=ui->le_prix->text();
   QString description=ui->le_description->text();
   QString fournisseur=ui->combo_fournisseur_2->currentText();
   QString date_achat=ui->le_dateachat->text();
   QString produit=ui->cb_produitcommande->currentText();

   achat a(num_commande,quantite,prix,description,fournisseur,date_achat,produit);
    bool test=a.ajouter();
    QMessageBox msgBox;

    if(test)
      {  msgBox.setText("Ajout avec succes.");
        ui->tabachat->setModel(a.afficher());
        ui->combo_fournisseur_2->addItem(fournisseur);


    }
    else
        msgBox.setText("Echec d'ajout");
        msgBox.exec();

}

void MainWindowAchat::on_pb_supprimer_2_clicked()
{
    son->play();
    achat a;
    achat a1;
    QMessageBox msgBox;
    if(a1.supprimer(achatselect))
       { msgBox.setText("Suppression avec succes.");
    ui->tabachat->setModel(a.afficher());
    //ui->combo_fournisseur->removeItem();

    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void MainWindowAchat::on_le_recherche_2_textChanged(const QString &arg1)
{
    achat a;
       ui->tabachat->setModel(a.rechercher(ui->comboBox->currentText(),arg1));
}

void MainWindowAchat::on_tabachat_clicked(const QModelIndex &index)
{
      achatselect=ui->tabachat->model()->data(index.sibling(index.row(),0)).toInt();
}

void MainWindowAchat::on_pb_modifier_5_clicked()
{
    son->play();

        QString prix, description, fournisseur,date_achat, produit;
            int quantite,num_commande;
            num_commande=ui->le_numcommande_3->text().toInt();
            quantite=ui->le_quantite_3->text().toInt();
            prix=ui->le_prix_3->text();
            description=ui->le_description_3->text();
            fournisseur=ui->combo_fournisseur->currentText();
            date_achat=ui->le_dateachat_3->text();
            produit=ui->le_produitachat_3->text();

            achat a(num_commande,quantite,prix,description,fournisseur,date_achat,produit);

            QMessageBox msgBox;
                if (a.modifier())
                {

                      msgBox.setText("Le Document a été modifié.");

                      ui->tabachat->setModel(a.afficher());

                }

                else
                {
                    msgBox.setText("échec de modification.");
                }
                msgBox.exec();
}

void MainWindowAchat::on_tabachat_activated()
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
            ui->combo_fournisseur->setCurrentText(query.value(4).toString());
            ui->le_dateachat_3->setText(query.value(5).toString());
            ui->le_produitachat_3->setText(query.value(6).toString());
        }

         }

        else {
                QMessageBox::critical(this,tr("error::"), query.lastError().text());
        }


}

void MainWindowAchat::on_tri_clicked()
{
    son->play();
       QString colone=ui->colone_tri->currentText();
           QString ordre=ui->ordre_tri->currentText();
           achat a;
           ui->tabachat->setModel(a.tri(colone,ordre));
}

void MainWindowAchat::on_pushButton_clicked()
{
    son->play();
       QPrinter printer;
                      QPrintDialog *printDialog = new QPrintDialog(&printer, this);
                      printDialog->setWindowTitle("Imprimer Document");
                      printDialog->exec();
}

void MainWindowAchat::on_PDF_clicked()
{
    son->play();
       QString strStream;
                                     QTextStream out(&strStream);

                                     const int rowCount = ui->tabachat->model()->rowCount();
                                     const int columnCount = ui->tabachat->model()->columnCount();

                                     out <<  "<html>\n"
                                         "<head>\n"
                                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                         <<  QString("<title>%1</title>\n").arg("strTitle")
                                         <<  "</head>\n"
                                         "<body bgcolor=#ffffff link=#5000A0>\n"

                                        //     "<align='right'> " << datefich << "</align>"
                                         "<center> <H1> ACHAT </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                     // headers
                                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                     for (int column = 0; column < columnCount; column++)
                                         if (!ui->tabachat->isColumnHidden(column))
                                             out << QString("<th>%1</th>").arg(ui->tabachat->model()->headerData(column, Qt::Horizontal).toString());
                                     out << "</tr></thead>\n";

                                     // data table
                                     for (int row = 0; row < rowCount; row++) {
                                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                         for (int column = 0; column < columnCount; column++) {
                                             if (!ui->tabachat->isColumnHidden(column)) {
                                                 QString data = ui->tabachat->model()->data(ui->tabachat->model()->index(row, column)).toString().simplified();
                                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                             }
                                         }
                                         out << "</tr>\n";
                                     }
                                     out <<  "</table> </center>\n"
                                         "</body>\n"
                                         "</html>\n";

                               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                QPrinter printer (QPrinter::PrinterResolution);
                                 printer.setOutputFormat(QPrinter::PdfFormat);
                                printer.setPaperSize(QPrinter::A4);
                               printer.setOutputFileName(fileName);

                                QTextDocument doc;
                                 doc.setHtml(strStream);
                                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                 doc.print(&printer);
}
