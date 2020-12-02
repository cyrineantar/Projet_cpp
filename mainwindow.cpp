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
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //controle de saisie:
    QRegExp n("[a-zA-Z0-9_]*");
    QValidator *validator =new QRegExpValidator(n, this);
    ui->lineEdit_ID->setValidator(new QIntValidator(0, 9999999, this));
    ui->lineEdit_salaire->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_numtelephone->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_id_conge->setValidator(new QIntValidator(0, 9999999, this));
    ui->lineEdit_nom->setValidator(validator);
    ui->lineEdit_prenom->setValidator(validator);
    ui->lineEdit_courriel->setValidator(validator);
    ui->lineEdit_adresse->setValidator(validator);
    ui->lineEdit_fonction->setValidator(validator);
    ui->lineEdit_nationalite->setValidator(validator);

    ui->tableView->setModel(E.afficher());
    ui->tableView_2->setModel(C.afficher_conge());
    remplir_cb_employID();



}


void MainWindow::remplir_cb_employID()
{

    QSqlQuery qry;
    qry.prepare("SELECT id FROM EMPLOYE");

    if(qry.exec())
    {
        while(qry.next())
        {
            ui->comboBox_emplo->addItem(qry.value(0).toString());

        }
    }


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
      QString Etat_civil=ui->lineEdit_Etatcivil->currentText();
      QString Nationalite=ui->lineEdit_nationalite->text();

      Employe E(ID,Nom,Prenom,Courriel,Num_tel,Date_n,Adresse,Fonction,Salaire,Etat_civil,Nationalite);

              bool test=E.ajouter();
              QMessageBox msgBox;

               if (test)
               {
                   msgBox.setText("Ajout avec succès.");
                   ui->tableView->setModel(E.afficher());
                   ui->comboBox_emplo->clear();
                   remplir_cb_employID();
               }
               else
               {
                   msgBox.setText("échec au niveau de l ajout");
               }
                   msgBox.exec();
}

void MainWindow::on_Modifier_clicked()
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
        QString Etat_civil=ui->lineEdit_Etatcivil->currentText();
        QString Nationalite=ui->lineEdit_nationalite->text();
          QMessageBox msg;

        bool test=E.modifier(ID,Nom,Prenom,Courriel,Num_tel,Date_n,Adresse,Fonction,Salaire,Etat_civil,Nationalite);


        if(test)
        {
            ui->lineEdit_ID->clear();
            ui->lineEdit_nom->clear();
            ui->lineEdit_prenom->clear();
            ui->lineEdit_courriel->clear();
            ui->lineEdit_numtelephone->clear();
            ui->lineEdit_adresse->clear();
            ui->lineEdit_fonction->clear();
            ui->lineEdit_salaire->clear();
            ui->lineEdit_nationalite->clear();

            ui->tableView->setModel(E.afficher());
            msg.setText("Modification avec succès");

         }
        else
        {
            msg.setText("Echec de modification");
        }
        msg.exec();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
        qry.prepare("select * from EMPLOYE where ID=:val");
        qry.bindValue(":val",val);

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_ID->setText(qry.value(0).toString());
                ui->lineEdit_nom->setText(qry.value(1).toString());
                ui->lineEdit_prenom->setText(qry.value(2).toString());
                ui->lineEdit_courriel->setText(qry.value(3).toString());
                ui->lineEdit_numtelephone->setText(qry.value(4).toString());
                ui->lineEdit_Date->setDate(QDate::fromString(qry.value(5).toString()));
                ui->lineEdit_adresse->setText(qry.value(6).toString());
                ui->lineEdit_fonction->setText(qry.value(7).toString());
                ui->lineEdit_salaire->setText(qry.value(8).toString());
                ui->lineEdit_Etatcivil->setCurrentText(qry.value(9).toString());
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
          { msgBox.setText("Suppression avec succes.");
       ui->tableView->setModel(E.afficher());
       ui->comboBox_emplo->clear();
       remplir_cb_employID();
       }
       else
           msgBox.setText("Echec de suppression");
           msgBox.exec();
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
                     "<center> <H1>Liste des employes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

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


void MainWindow::on_Ajouter_conge_clicked()
{
    int ID_conge=ui->lineEdit_id_conge->text().toInt();
    int ID=ui->comboBox_emplo->currentText().toInt();
    QString Date_debut=ui->lineEdit_datedebut->text();
    QString Date_fin=ui->lineEdit_datefin->text();
    QString Motif=ui->lineEdit_motif->text();
    QString Type_conge=ui->lineEdit_typeconge->currentText();

    conge C(ID_conge, ID, Date_debut, Date_fin, Motif, Type_conge);

            bool test=C.ajouter_conge();
            QMessageBox MsgBox;

             if (test)
             {
                 MsgBox.setText("Ajout avec succès.");
                 ui->tableView_2->setModel(C.afficher_conge());
             }
             else
             {
                 MsgBox.setText("échec au niveau de l ajout");
             }
                 MsgBox.exec();
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    QString val=ui->tableView_2->model()->data(index).toString();
    QSqlQuery qry;
        qry.prepare("Select * from CONGE where ID_conge=:val  " );

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_id_conge->setText(qry.value(0).toString());
                int i=0;
                ui->comboBox_emplo->setCurrentIndex(0);
                while(qry.value(1).toString()!= ui->comboBox_emplo->currentText())
                {
                    i++;
                    ui->comboBox_emplo->setCurrentIndex(i);

                }
                ui->lineEdit_datedebut-> setDate(QDate::fromString(qry.value(2).toString(),"dd/MM/yyyy"));
                ui->lineEdit_datefin->setDate(QDate::fromString(qry.value(3).toString(),"dd/MM/yyyy"));
                ui->lineEdit_motif->setText(qry.value(4).toString());
                ui->lineEdit_typeconge->setCurrentText(qry.value(5).toString());

            }
        }
}

void MainWindow::on_Supprimer_conge_clicked()
{
    conge C1;
    C1.setID_conge(ui->le_id_conge_suppr->text().toInt());
       bool test=C1.supprimer_conge(C1.get_ID_conge());
       QMessageBox msgBox;
       if(test)
          { msgBox.setText("Suppression avec succes.");
       ui->tableView_2->setModel(C.afficher_conge());
       }
       else
           msgBox.setText("Echec de suppression");
           msgBox.exec();
}

void MainWindow::on_Tri_conge_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM CONGE order by ID_conge ASC");
             model->setQuery("SELECT * FROM CONGE order by ID ASC");
             model->setQuery("SELECT * FROM CONGE order by Type_conge ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_conge"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_debut"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_fin"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Motif"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type_conge"));

             ui->tableView_2->setModel(model);
             ui->tableView_2->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void MainWindow::on_Modifier_conge_clicked()
{
    int ID_conge=ui->lineEdit_id_conge->text().toInt();
    int ID_employe=ui->comboBox_emplo->currentText().toInt();
    QString Date_debut=ui->lineEdit_datedebut->text();
    QString Date_fin=ui->lineEdit_datefin->text();
    QString Motif=ui->lineEdit_motif->text();
    QString Type_conge=ui->lineEdit_typeconge->currentText();

    bool test=C.modifier_conge(ID_conge,ID_employe,Date_debut,Date_fin,Motif,Type_conge);
    QMessageBox msgBox;
    if(test)
    {
         ui->tableView_2->setModel(C.afficher_conge());
        msgBox.setText("Modification réussite");
    }
    else
    {
        msgBox.setText("Erreur de modification");
    }
    msgBox.exec();
}

void MainWindow::on_Pdf_conge_clicked()
{
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
                     "<center> <H1>Liste des conges </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

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
             doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
             doc.print(&printer);

}

void MainWindow::on_Imprimer_conge_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;
}

void MainWindow::on_Quitter_2_clicked()
{
    close();
}

void MainWindow::on_Rechercher_2_clicked()
{

}


void MainWindow::on_tableView_recherche_clicked(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
        qry.prepare("select * from EMPLOYE where ID=:val");
        qry.bindValue(":val",val);

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_ID->setText(qry.value(0).toString());
                ui->lineEdit_nom->setText(qry.value(1).toString());
                ui->lineEdit_prenom->setText(qry.value(2).toString());
                ui->lineEdit_courriel->setText(qry.value(3).toString());
                ui->lineEdit_numtelephone->setText(qry.value(4).toString());
                ui->lineEdit_Date->setDate(QDate::fromString(qry.value(5).toString()));
                ui->lineEdit_adresse->setText(qry.value(6).toString());
                ui->lineEdit_fonction->setText(qry.value(7).toString());
                ui->lineEdit_salaire->setText(qry.value(8).toString());
                ui->lineEdit_Etatcivil->setCurrentText(qry.value(9).toString());
                ui->lineEdit_nationalite->setText(qry.value(10).toString());


            }
        }
}


void MainWindow::on_Rechercher_clicked()
{
    Employe E1;
    E1.setID(ui->lineEdit_id_rech->text().toInt());
    QMessageBox msgBox ;
    QSqlQueryModel *model = new QSqlQueryModel();

        model->setQuery("SELECT * FROM EMPLOYE where ID=:ID");
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
        qry.prepare("SELECT * FROM EMPLOYE where ID=:ID");

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_ID->setText(qry.value(0).toString());
                ui->lineEdit_nom->setText(qry.value(1).toString());
                ui->lineEdit_prenom->setText(qry.value(2).toString());
                ui->lineEdit_courriel->setText(qry.value(3).toString());
                ui->lineEdit_numtelephone->setText(qry.value(4).toString());
                ui->lineEdit_Date->setDate(QDate::fromString(qry.value(5).toString()));
                ui->lineEdit_adresse->setText(qry.value(6).toString());
                ui->lineEdit_fonction->setText(qry.value(7).toString());
                ui->lineEdit_salaire->setText(qry.value(8).toString());
                ui->lineEdit_Etatcivil->setCurrentText(qry.value(9).toString());
                ui->lineEdit_nationalite->setText(qry.value(10).toString());
            }
        }

}
