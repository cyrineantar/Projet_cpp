#include "espace_livraison.h"
#include "ui_espace_livraison.h"
#include "livraison.h"
#include "vente.h"
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
#include <arduino.h>

Espace_livraison::Espace_livraison(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Espace_livraison)
{
    livraison L;
    vente v;
    ui->setupUi(this);
    son=new QSound(":/sons/mouse.wav");
    ui->num_com->setValidator(new QIntValidator(0, 9999999, this));
    ui->num_vente->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(L.afficher());
    ui->tableView_2->setModel(v.afficher1());


    // setup Arduino

    int ret = A.connect_arduino();
                switch (ret)
                {
                    case(0):qDebug()<<"arduino is available and connected to :" << A.getarduino_port_name();
                    break;
                    case(1):qDebug()<<"arduino is available but not connected to :" << A.getarduino_port_name();
                    break;
                    case(-1):qDebug()<<"arduino is not available";
                    break;

                }
                QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));


}

Espace_livraison::~Espace_livraison()
{
    delete ui;
}
void Espace_livraison::on_Ajouter_clicked()
{     son->play();
      int num_com=ui->num_com->text().toInt();
      QString produit=ui->produit->currentText();
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


void Espace_livraison::on_le_recherche_textChanged(const QString &arg1)
{
    livraison L;
        ui->tableView->setModel(L.rechercher(ui->cb_recherche->currentText(),arg1));
}



void Espace_livraison::on_supprimer_clicked()
{   son->play();
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

void Espace_livraison::on_modifier_2_clicked()
{   son->play();
    int num_com,quantite,total;
   QString produit,livreur,date_arrivee;

   num_com=ui->num_com_2->text().toInt();
   produit=ui->produit_2->currentText();
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

void Espace_livraison::on_button_tri_clicked()
{    son->play();
    QString colone=ui->colone_tri->currentText();
        QString ordre=ui->ordre_tri->currentText();
        livraison L;
        ui->tableView->setModel(L.tri(colone,ordre));
}

void Espace_livraison::on_imprimer_clicked()
{    son->play();
    QPrinter printer;
                QPrintDialog *printDialog = new QPrintDialog(&printer, this);
                printDialog->setWindowTitle("Imprimer Document");
                printDialog->exec();
}

void Espace_livraison::on_PDF_clicked()
{    son->play();
    QString strStream;
                                QTextStream out(&strStream);

                                const int rowCount = ui->tableView->model()->rowCount();
                                const int columnCount = ui->tableView->model()->columnCount();

                                out <<  "<html>\n"
                                    "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                    <<  QString("<title>%1</title>\n").arg("strTitle")
                                    <<  "</head>\n"
                                    "<body bgcolor=#ffffff link=#5000A0>\n"

                                   //     "<align='right'> " << datefich << "</align>"
                                    "<center> <H1> LISTE DE LIVRAISON </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                // headers
                                out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                for (int column = 0; column < columnCount; column++)
                                    if (!ui->tableView->isColumnHidden(column))
                                        out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                                out << "</tr></thead>\n";

                                // data table
                                for (int row = 0; row < rowCount; row++) {
                                    out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                    for (int column = 0; column < columnCount; column++) {
                                        if (!ui->tableView->isColumnHidden(column)) {
                                            QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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





void Espace_livraison::on_tabWidget_2_tabBarClicked(int index)
{
    livraison L;
    if (index==1)
         ui->tableView->setModel(L.afficher());

}



    void Espace_livraison::on_ajouter1_clicked()
    {
           son->play();
          int num_vente=ui->num_vente->text().toInt();
          QString prod=ui->nom_pro->currentText();
          int quant=ui->laquantite->text().toInt();
          int id=ui->ID->text().toInt();
          int tot=ui->le_total->text().toInt();
          QString date_arr=ui->la_date->text();

   vente V(num_vente,prod,quant,id,tot,date_arr);

     bool test=V.ajouter1();
     QMessageBox msgBox;

    if(test)
     {
        msgBox.setText("Ajout avec succes.");
        ui->tableView_2->setModel(V.afficher1());

     }
     else
    {
   msgBox.setText("Echec d'ajout");
   msgBox.exec();

}

}



void Espace_livraison::on_le_recherche_2_textChanged(const QString &arg1)
{
   vente V;
        ui->tableView_2->setModel(V.rechercher1(ui->cb_recherche_2->currentText(),arg1));
}




void Espace_livraison::on_button_tri_2_clicked()
{      son->play();
        QString colone=ui->colone_tri_2->currentText();
        QString ordre=ui->ordre_tri_2->currentText();
          vente V;
           ui->tableView_2->setModel(V.tri1(colone,ordre));
}



void Espace_livraison::on_supprimer_2_clicked()
{      son->play();
     int num_vente =ui->le_supprimer_2->text().toInt();
      vente V;
     V.setnum_vente(num_vente);
    QMessageBox msg;
    if(V.supprimer1())
    {
        msg.setText("suppression avec succés");
        ui->tableView_2->setModel(V.afficher1());

    }
    else
    {
        msg.setText("echec de suppression");
    }
    msg.exec();

}

void Espace_livraison::on_imprimer_2_clicked()
{    son->play();
    QPrinter printer;
                QPrintDialog *printDialog = new QPrintDialog(&printer, this);
                printDialog->setWindowTitle("Imprimer Document");
                printDialog->exec();

}

void Espace_livraison::on_PDF_2_clicked()
{    son->play();
    QString strStream;
                                QTextStream out(&strStream);

                                const int rowCount = ui->tableView_2->model()->rowCount();
                                const int columnCount = ui->tableView_2->model()->columnCount();

                                out <<  "<html>\n"
                                    "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                    <<  QString("<title>%1</title>\n").arg("strTitle")
                                    <<  "</head>\n"
                                    "<body bgcolor=#ffffff link=#5000A0>\n"

                                   //     "<align='right'> " << datefich << "</align>"
                                    "<center> <H1> LISTE DE LIVRAISON </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                // headers
                                out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                for (int column = 0; column < columnCount; column++)
                                    if (!ui->tableView_2->isColumnHidden(column))
                                        out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
                                out << "</tr></thead>\n";

                                // data table
                                for (int row = 0; row < rowCount; row++) {
                                    out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                    for (int column = 0; column < columnCount; column++) {
                                        if (!ui->tableView_2->isColumnHidden(column)) {
                                            QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
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
                            doc.setPageSize(printer.pageRect().size());
                            doc.print(&printer);
}

void Espace_livraison::on_modifier3_clicked()
{
    son->play();
    int num_vente,quant,id,tot;
    QString prod,date_arr;

    num_vente=ui->numventemodif->text().toInt();
    prod=ui->prod_modif->currentText();
    quant=ui->quantmodif->text().toInt();
    id=ui->idmodif->text().toInt();
    tot=ui->totmodif->text().toInt();
    date_arr=ui->datemodif->text();

    vente V(num_vente,prod,quant,id,tot,date_arr);

    QMessageBox msgBox;
        if (V.modifier1())
        {

              msgBox.setText("Le Document a été modifié.");

              ui->tableView_2->setModel(V.afficher1());

        }

        else
        {
            msgBox.setText("échec de modification.");
        }
        msgBox.exec();


}



void Espace_livraison::on_affichage2_tabBarClicked(int index)
{ vente V;
    if (index==1)
          ui->tableView_2->setModel(V.afficher1());
}


