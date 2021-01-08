#include "espace_client.h"
#include "ui_espace_client.h"




Espace_client::Espace_client(QWidget *parent)
    :  QDialog(parent)
    , ui(new Ui::Espace_client)
{
    ui->setupUi(this);
    QValidator *validInt = new QIntValidator(10000000,99999999, this);
    ui->le_tel->setValidator(validInt);
    ui->le_tel_modif->setValidator(validInt);
    ui->le_fax->setValidator(validInt);
    ui->le_fax_modif->setValidator(validInt);
    afficher_tabClient();
    afficher_tab_carteFid();


}

Espace_client::~Espace_client()
{
    delete ui;
}

void Espace_client::afficher_tabClient()
{
    //creation model (masque du tableau) : permet recherche et tri
        proxy = new QSortFilterProxyModel();

     //definir la source (tableau original)
        proxy->setSourceModel(c.afficher());

     //pour la recherche
        proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
        proxy->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
       //remplissage tableau avec le masque
        ui->tabClient->setModel(proxy);

}

void Espace_client::afficher_tab_carteFid()
{

    //creation model (masque du tableau) : permet recherche et tri
        proxy_carteFid = new QSortFilterProxyModel();

     //definir la source (tableau original)
        proxy_carteFid->setSourceModel(carte.afficher());

     //pour la recherche
        proxy_carteFid->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
        proxy_carteFid->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
       //remplissage tableau avec le masque
        ui->tabCarteFid->setModel(proxy_carteFid);

}




void Espace_client::on_button_ajouterClient_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Espace_client::on_validerAjout_accepted()
{
   //recuperation des données
    QString nomEntreprise=ui->le_nomEntreprise->text();
    QString description=ui->text_description->toPlainText();
    QString matriculeFiscale=ui->le_matriculeFiscale->text();
    QString Email=ui->le_email->text();
    QString adresse=ui->le_adresse->text();
    QString ville=ui->le_ville->text();
    int codePostal=ui->sb_codePostal->text().toInt();
    QString numTel=ui->le_tel->text();
    QString numFax=ui->le_fax->text();

  Client c(nomEntreprise,description,matriculeFiscale,Email,adresse,ville,codePostal,numTel,numFax);
  c.ajouter();

    ui->stackedWidget->setCurrentIndex(0);
    afficher_tabClient();
}





//recherche dynamique



void Espace_client::on_lineEdit_textChanged(const QString &arg1)
{
    int coloneR=ui->cb_colone->currentIndex()-1;
    proxy->setFilterKeyColumn(coloneR);
    proxy->setFilterFixedString(arg1);
}

void Espace_client::on_validerModif_accepted()
{
    QString nomEntreprise=ui->le_nomEntreprise_modif->text();
    QString description=ui->text_description_modif->toPlainText();
    QString matriculeFiscale=ui->le_matriculeFiscale_modif->text();
    QString Email=ui->le_email_modif->text();
    QString adresse=ui->le_adresse_modif->text();
    QString ville=ui->le_ville_modif->text();
    int codePostal=ui->sb_codePostal_modif->value();
    QString numTel=ui->le_tel_modif->text();
    QString numFax=ui->le_fax_modif->text();

  Client c(nomEntreprise,description,matriculeFiscale,Email,adresse,ville,codePostal,numTel,numFax);
  c.modifier();

    ui->stackedWidget->setCurrentIndex(0);
    afficher_tabClient();

}

void Espace_client::on_tabClient_clicked(const QModelIndex &index)
{

    clientSelectionne= ui->tabClient->model()->data( index.sibling(index.row(),2)).toString();

}

void Espace_client::on_tabClient_activated()
{
    ui->stackedWidget->setCurrentIndex(2);
    //remplir les champs pour modifier
    QSqlQuery query;
    query.prepare("select * from client where matricule_fiscale = :mf_clientSelectionne");
    query.bindValue(":mf_clientSelectionne",clientSelectionne);
    if(query.exec())
    {
        while(query.next())
        {
            ui->le_nomEntreprise_modif->setText(query.value(0).toString());
            ui->text_description_modif->setText(query.value(1).toString());
            ui->le_matriculeFiscale_modif->setText(query.value(2).toString());
            ui->le_email_modif->setText(query.value(3).toString());
            ui->le_adresse_modif->setText(query.value(4).toString());
            ui->le_ville_modif->setText(query.value(5).toString());
            ui->sb_codePostal_modif->setValue(query.value(6).toInt());
            ui->le_tel_modif->setText(query.value(7).toString());
             ui->le_fax_modif->setText(query.value(8).toString());

        }
    }



}

void Espace_client::on_validerAjout_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Espace_client::on_validerModif_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Espace_client::on_button_supprimerClient_clicked()
{
    Client c;
    c.supprimer(clientSelectionne);
    afficher_tabClient();

}

void Espace_client::on_button_ajouter_carteFid_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

    //afficher les matricules des entreprises dans le combo box
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT MATRICULE_FISCALE FROM CLIENT");
    ui->cb_matriculeFiscale->setModel(model);
}

void Espace_client::on_validerAjout_cf_accepted()
{
    int numCarte=ui->sb_numCarte->value();
    QString date_de_creation=ui->le_dateCreation->text();
    int points=ui->sb_points->value();
    double totalAchats=ui->dsb_totalAchats->value();
    QString statuts=ui->cb_Status->currentText();
    int remise=ui->sb_remise->value();
    QString matriculeFiscale=ui->cb_matriculeFiscale->currentText();

    CarteFidelite carte(numCarte,date_de_creation,points,totalAchats,statuts,remise,matriculeFiscale);

    carte.ajouter();
    ui->stackedWidget_2->setCurrentIndex(0);
    afficher_tab_carteFid();

}

void Espace_client::on_le_recherche_carteFid_textChanged(const QString &arg1)
{
    int coloneR=ui->cb_colone_carteFid->currentIndex()-1;
    proxy_carteFid->setFilterKeyColumn(coloneR);
    proxy_carteFid->setFilterFixedString(arg1);

}

void Espace_client::on_tabCarteFid_clicked(const QModelIndex &index)
{
    carteSelectionne=ui->tabCarteFid->model()->data(index.sibling(index.row(),0)).toInt();
}

void Espace_client::on_tabCarteFid_activated()
{
     ui->stackedWidget_2->setCurrentIndex(2);
     QSqlQuery query;
     query.prepare("select * from CARTE_FIDELITE where NUM_CARTE = :NUM_CARTE");
     query.bindValue(":NUM_CARTE",carteSelectionne);
     if(query.exec())
     {
         while(query.next())
         {
             ui->sb_numCarte_modif->setValue(query.value(0).toInt());
             ui->le_dateCreation_modif->setDate(QDate::fromString(query.value(1).toString(),"dd/MM/yyyy"));
             ui->sb_points_modif->setValue(query.value(2).toInt());
             ui->dsb_totalAchats_modif->setValue(query.value(3).toDouble());
             ui->cb_Status_modif->setCurrentIndex( ui->cb_Status_modif->findText(query.value(4).toString(),Qt::MatchExactly));
             ui->sb_remise_modif->setValue(query.value(5).toInt());

         }

      }

}

void Espace_client::on_button_supprimer_carteFid_clicked()
{
    CarteFidelite cf;
    cf.setnumCarte(carteSelectionne);
    cf.supprimer();
    afficher_tab_carteFid();
}

void Espace_client::on_validerAjout_cf_rejected()
{
     ui->stackedWidget_2->setCurrentIndex(0);
}

void Espace_client::on_validerModif_cf_rejected()
{
     ui->stackedWidget_2->setCurrentIndex(0);
}



void Espace_client::on_validerModif_cf_accepted()
{
    int numCarte=ui->sb_numCarte_modif->value();
    QString date_de_creation=ui->le_dateCreation_modif->text();
    int points=ui->sb_points_modif->value();
    double totalAchats=ui->dsb_totalAchats_modif->value();
    QString statuts=ui->cb_Status_modif->currentText();
    int remise=ui->sb_remise_modif->value();
    QString matriculeFiscale;

    CarteFidelite carte(numCarte,date_de_creation,points,totalAchats,statuts,remise,matriculeFiscale);

    carte.modifier();
    ui->stackedWidget_2->setCurrentIndex(0);
    afficher_tab_carteFid();
}

void Espace_client::on_Button_pdf_clicked()
{

     QString strStream;
                              QTextStream out(&strStream);

                              const int rowCount = ui->tabClient->model()->rowCount();
                              const int columnCount = ui->tabClient->model()->columnCount();

                              out <<  "<html>\n"
                                  "<head>\n"
                                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                  <<  QString("<title>%1</title>\n").arg("strTitle")
                                  <<  "</head>\n"
                                  "<body bgcolor=#ffffff link=#5000A0>\n"

                                 //     "<align='right'> " << datefich << "</align>"
                                  "<center> <H1>client </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                              // headers
                              out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                              for (int column = 0; column < columnCount; column++)
                                  if (!ui->tabClient->isColumnHidden(column))
                                      out << QString("<th>%1</th>").arg(ui->tabClient->model()->headerData(column, Qt::Horizontal).toString());
                              out << "</tr></thead>\n";

                              // data table
                              for (int row = 0; row < rowCount; row++) {
                                  out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                  for (int column = 0; column < columnCount; column++) {
                                      if (!ui->tabClient->isColumnHidden(column)) {
                                          QString data = ui->tabClient->model()->data(ui->tabClient->model()->index(row, column)).toString().simplified();
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
