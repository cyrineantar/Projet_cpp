#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ID->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(E.afficher());

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Ajouter_clicked()
{

      int ID=ui->lineEdit_ID->text().toInt();
      QString Nom=ui->lineEdit_nom->text();
      QString Prenom=ui->lineEdit_prenom->text();
      QString Courriel=ui->lineEdit_courriel->text();
      int Num_tel=ui->lineEdit_numtelephone->text().toInt();
      QString Date_n=ui->lineEdit_Date->text();
      QString Adresse=ui->lineEdit_adresse->text();
      QString Fonction=ui->lineEdit_fonction->text();
      int Salaire=ui->lineEdit_salaire->text().toInt();
      QString Etat_civil=ui->lineEdit_Etatcivil->text();
      QString Nationalite=ui->lineEdit_nationalite->text();

      Employe E(ID,Nom,Prenom,Courriel,Num_tel,Date_n,Adresse,Fonction,Salaire,Etat_civil,Nationalite);

              bool test=E.ajouter();
              QMessageBox msgBox;

               if (test)
               {
                   msgBox.setText("Ajout avec succès.");
                   ui->tableView->setModel(E.afficher());
               }
               else
               {
                   msgBox.setText("échec au niveau de l ajout");
               }
                   msgBox.exec();
}

void MainWindow::on_Modifier_clicked()
{
     ui->tableView->setModel(E.afficher());
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        int ID=ui->lineEdit_ID->text().toInt();
        QString Nom=ui->lineEdit_nom->text();
        QString Prenom=ui->lineEdit_prenom->text();
        QString Courriel=ui->lineEdit_courriel->text();
        int Num_tel=ui->lineEdit_numtelephone->text().toInt();
        QString Date_n=ui->lineEdit_Date->text();
        QString Adresse=ui->lineEdit_adresse->text();
        QString Fonction=ui->lineEdit_fonction->text();
        int Salaire=ui->lineEdit_salaire->text().toInt();
        QString Etat_civil=ui->lineEdit_Etatcivil->text();
        QString Nationalite=ui->lineEdit_nationalite->text();

        Employe E;
        bool test=E.modifier(ID, Nom, Prenom,Courriel,Num_tel,Date_n,Adresse,Fonction,Salaire,Etat_civil,Nationalite);
        QMessageBox msBox;
        if(test)
        {
            ui->tableView->setModel(E.afficher());
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            msBox.setText("Modification réussite");
            msBox.exec();
        }
        else
        {
            msBox.setText("ERREUR");
            msBox.exec();
        }

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
        qry.prepare("select * from EMPLOYE where ID='"+val+"'  " );

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_ID->setText(qry.value(0).toString());
                ui->lineEdit_nom->setText(qry.value(1).toString());
                ui->lineEdit_prenom->setText(qry.value(2).toString());
                ui->lineEdit_courriel->setText(qry.value(3).toString());
                ui->lineEdit_numtelephone->setText(qry.value(4).toString());
                ui->lineEdit_Date->setText(qry.value(5).toString());
                ui->lineEdit_adresse->setText(qry.value(6).toString());
                ui->lineEdit_fonction->setText(qry.value(7).toString());
                ui->lineEdit_salaire->setText(qry.value(8).toString());
                ui->lineEdit_Etatcivil->setText(qry.value(9).toString());
                ui->lineEdit_nationalite->setText(qry.value(10).toString());


            }
        }
}
void MainWindow::on_Supprimer_clicked()
{
    Employe E1;
    E1.setID(ui->le_id_suppr->text().toInt());
       bool test=E1.supprimer(E1.get_ID());
       QMessageBox msgBox;
       if(test)
           msgBox.setText("Suppression avec succes.");
       else
           msgBox.setText("Echec de suppression");
           msgBox.exec();
}




void MainWindow::on_Rechercher_clicked()
{
    QMessageBox msgBox ;
    QSqlQueryModel *model = new QSqlQueryModel();
        int ID;
        ID=ui->lineEdit_id_rech->text().toInt();
        model->setQuery("SELECT * FROM EMPLOYE where ID='ID'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Courriel"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Num_tel"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_n"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Fonction"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Etat_civil"));
        model->setHeaderData(10, Qt::Horizontal, QObject::tr("Natioanlite"));
        ui->tableView->setModel(model);
        ui->tableView->show();
        msgBox.setText("Employé trouvé.");
        msgBox.exec();
        ui->lineEdit_id_rech->clear();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM EMPLOYE where ID='ID'");

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_ID->setText(qry.value(0).toString());
                ui->lineEdit_nom->setText(qry.value(1).toString());
                ui->lineEdit_prenom->setText(qry.value(2).toString());
                ui->lineEdit_courriel->setText(qry.value(3).toString());
                ui->lineEdit_numtelephone->setText(qry.value(4).toString());
                ui->lineEdit_Date->setText(qry.value(5).toString());
                ui->lineEdit_adresse->setText(qry.value(6).toString());
                ui->lineEdit_fonction->setText(qry.value(7).toString());
                ui->lineEdit_salaire->setText(qry.value(8).toString());
                ui->lineEdit_Etatcivil->setText(qry.value(9).toString());
                ui->lineEdit_nationalite->setText(qry.value(10).toString());
            }
        }
}

void MainWindow::on_Tri_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM EMPLOYE order by ID ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Courriel"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Num_tel"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_n"));
             model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(7, Qt::Horizontal, QObject::tr("Fonction"));
             model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
             model->setHeaderData(9, Qt::Horizontal, QObject::tr("Etat_civil"));
             model->setHeaderData(10, Qt::Horizontal, QObject::tr("Natioanlite"));
             ui->tableView->setModel(model);
             ui->tableView->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}


void MainWindow::on_Pdf_clicked()
{
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
                     "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

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

void MainWindow::on_Imprimer_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;
}

void MainWindow::on_Quitter_clicked()
{
    close();
}
