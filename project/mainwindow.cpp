#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    son=new QSound(":/son/click.wav");
    ui->le_numero->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_rib->setValidator(new QIntValidator(0, 9999999, this));

ui->tabfournisseur->setModel(f.afficher());
//ui->tabachat->setModel(a.afficher());
QSqlQuery query;
      /*  query.prepare("SELECT NOM FROM FOURNISSEUR");
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
                }*/
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{     son->play();
    int numero=ui->le_numero->text().toInt();
int rib=ui->le_rib->text().toInt();
QString nom=ui->le_nom->text();
QString matricule=ui->le_matricule->text();
QString produit=ui->cb_produit->currentText();
QString adresse=ui->le_adresse->text();
QString date=ui->date_fourniseur->text();
fournisseur f(numero,rib,nom,matricule,produit,adresse,date);
 bool test=f.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tabfournisseur->setModel(f.afficher());
     //ui->combo_fournisseur->addItem(nom);


 }
 else
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}

void MainWindow::on_pb_supprimer_clicked()
{    son->play();

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

/*void MainWindow::on_pb_ajoutercommande_clicked()
{    son->play();
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
*/
void MainWindow::on_tabfournisseur_activated()
{

      QSqlQuery query;
      query.prepare("SELECT * FROM FOURNISSEUR WHERE matricule=:fournisseurSelect");
      query.bindValue(":fournisseurSelect",fournisseurSelect);
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
{       son->play();
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

/*void MainWindow::on_pb_supprimer_2_clicked()
{        son->play();
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
}*/

/*void MainWindow::on_le_recherche_2_textChanged(const QString &arg1)
{
    achat a;
       ui->tabachat->setModel(a.rechercher(ui->comboBox->currentText(),arg1));
}*/

/*void MainWindow::on_tabachat_clicked(const QModelIndex &index)
{
    achatselect=ui->tabachat->model()->data(index.sibling(index.row(),0)).toInt();

}*/

/*void MainWindow::on_pb_modifier_5_clicked()
{     son->play();

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


}*/

/*void MainWindow::on_tabachat_activated()
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

}*/

/*void MainWindow::on_tri_clicked()
{     son->play();
    QString colone=ui->colone_tri->currentText();
        QString ordre=ui->ordre_tri->currentText();
        achat a;
        ui->tabachat->setModel(a.tri(colone,ordre));
}
*/


/*void MainWindow::on_pushButton_clicked()
{     son->play();
    QPrinter printer;
                   QPrintDialog *printDialog = new QPrintDialog(&printer, this);
                   printDialog->setWindowTitle("Imprimer Document");
                   printDialog->exec();
}

*/

/*void MainWindow::on_PDF_clicked()
{     son->play();
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
}*/

void MainWindow::on_tri_fournisseur_clicked()
{     son->play();
    QString colone=ui->colone_tri_1->currentText();
        QString ordre=ui->ordre_tri_2->currentText();
        fournisseur f;
        ui->tabfournisseur->setModel(f.tri(colone,ordre));
}

void MainWindow::on_imprimer_fournisseur_clicked()
{     son->play();
    QPrinter printer;
                   QPrintDialog *printDialog = new QPrintDialog(&printer, this);
                   printDialog->setWindowTitle("Imprimer Document");
                   printDialog->exec();
}

void MainWindow::on_pdf_clicked()
{     son->play();
    QString strStream;
                                  QTextStream out(&strStream);

                                  const int rowCount = ui->tabfournisseur->model()->rowCount();
                                  const int columnCount = ui->tabfournisseur->model()->columnCount();

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
                                      if (!ui->tabfournisseur->isColumnHidden(column))
                                          out << QString("<th>%1</th>").arg(ui->tabfournisseur->model()->headerData(column, Qt::Horizontal).toString());
                                  out << "</tr></thead>\n";

                                  // data table
                                  for (int row = 0; row < rowCount; row++) {
                                      out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                      for (int column = 0; column < columnCount; column++) {
                                          if (!ui->tabfournisseur->isColumnHidden(column)) {
                                              QString data = ui->tabfournisseur->model()->data(ui->tabfournisseur->model()->index(row, column)).toString().simplified();
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
