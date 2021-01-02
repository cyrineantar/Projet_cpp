#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include "exportexcelobject.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    show_tables(p.afficherProduit(),ui->tabProduits);
    show_tables(mp.afficherMP(),ui->tabMP);
    show_tables(mp.afficherMP(),ui->tab_affectMP);
    show_tables(mp.afficherMP(),ui->tab_affectMP_modif);

    //controle de saisie :
    QRegExp rx("[a-zA-Z0-9_]*");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->le_ajout_reference ->setValidator(validator) ;
    ui->le_ajout_emplacement ->setValidator(validator) ;
    ui->le_modif_emplacement->setValidator(validator) ;
    ui->le_modif_reference->setValidator(validator) ;
    ui->le_ajout_referenceMP->setValidator(validator) ;
    ui->le_ajout_emplacementMP ->setValidator(validator) ;
    ui->le_modif_emplacementMP->setValidator(validator) ;
    ui->le_modif_referenceMP->setValidator(validator) ;


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::show_tables(QSqlQueryModel * model,QTableView *tab){
//creation model (masque du tableau) : permet recherche et tri
    proxy = new QSortFilterProxyModel();

 //definir la source (tableau original)
    proxy->setSourceModel(model);

   //remplissage tableau avec le masque
   tab->setModel(proxy);

}

void MainWindow::recherche(QSqlQueryModel* model , QTableView * tab, QComboBox * indexColone, QLineEdit * le_recherche)
{
 proxy = new QSortFilterProxyModel();
 proxy->setSourceModel(model);
 proxy->setFilterFixedString(le_recherche->text());
 proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
 proxy->setFilterKeyColumn(indexColone->currentIndex()-1);// chercher dans la coloune ou donner le numero de la colone
 tab->setModel(proxy);
}

//recherche si le texte de recherche a été changée
void MainWindow::on_le_rechercheP_textChanged()
{

    recherche(p.afficherProduit() ,ui->tabProduits, ui->cb_champ,ui->le_rechercheP);

}
//recherche si la colone de recherche a été changée
void MainWindow::on_cb_champ_currentIndexChanged(int index)
{
    recherche(p.afficherProduit() ,ui->tabProduits, ui->cb_champ,ui->le_rechercheP);

}


//aller à l'interface de l'ajout
void MainWindow::on_Button_Ajouter_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);


}


void MainWindow::on_Button_Supprimer_clicked()
{
    Produit p;

       QMessageBox msg;
       bool test=p.supprimerProduit(produitSelectionne);
       if (test)
       {
          msg.setText("suppresion avec succes.");
          ui->tab_ref_mpAffecte->setModel(p.afficher_MPaffecte());
          msg.setIcon(QMessageBox::Information);
          show_tables(p.afficherProduit(),ui->tabProduits);
           msg.exec();
       }

}



void MainWindow::remplir_champsModifP()
{
    QSqlQuery query;
 query.prepare("select * from produit where Reference= :refProduit");
 query.bindValue(":refProduit",produitSelectionne);
 if(query.exec())
 {
     while(query.next())
     {
         int i=0;
         ui->cb_modif_categorie->setCurrentIndex(0);
         while(ui->cb_modif_categorie->currentText()!=query.value(0).toString())
         {
             i++;
             ui->cb_modif_categorie->setCurrentIndex(i);
         }
         ui->le_modif_description->setText(query.value(1).toString());
         ui->le_modif_reference->setText(query.value(2).toString());
         ui->le_modif_quantite->setValue(query.value(3).toInt());
         ui->date_creation_modif->setDate(QDate::fromString(query.value(4).toString(),"dd/MM/yyyy"));
         ui->date_expiration_modif->setDate(QDate::fromString(query.value(5).toString(),"dd/MM/yyyy"));
         ui->le_modif_emplacement->setText(query.value(6).toString());
         ui->le_modif_prix->setValue(query.value(7).toDouble());
         ui->le_modif_dimensions->setValue(query.value(8).toDouble());
         ui->le_modif_poids->setValue(query.value(9).toDouble());
         ui->le_modif_volume->setValue(query.value(10).toDouble());
         ui->le_modif_commentaire->setText(query.value(11).toString());

     }
 }

}
void MainWindow::on_tabProduits_activated()
{
    //passer a la page modif
    ui->stackedWidget->setCurrentIndex(2);
    //Remplir les champs
    remplir_champsModifP();

}



void MainWindow::on_tabProduits_clicked(const QModelIndex &index)
{
    produitSelectionne=ui->tabProduits->model()->data(index.sibling(index.row(),2)).toString();
    Produit p;
    p.setReference(produitSelectionne);

    ui->tab_ref_mpAffecte->setModel(p.afficher_MPaffecte());

}

void MainWindow::on_button_okAjout_accepted()
{

    if(ui->date_creation_ajout->date() > ui->date_expiration_ajout->date())
    {
        QMessageBox msg;
        msg.setText("impossible d'insérer une date d'expiration inférieur à la date de création!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }

    int Quantite=ui->le_ajout_quantite->value();
    double Prix= ui->le_ajout_prix->value();
    double Dimensions= ui->le_ajout_dimensions->value();
    double Poids= ui->le_ajout_poids->value();
    double Volume= ui->le_ajout_volume->value();
    QString Categorie= ui->cb_ajoutCategorie->currentText();
    QString Description= ui->le_ajout_description->text();
    QString Reference= ui->le_ajout_reference->text();
    QString Emplacement= ui->le_ajout_emplacement->text();
    QString Date_de_creation= ui->date_creation_ajout->text();
    QString Date_d_expiration= ui->date_expiration_ajout->text();
    QString Commentaire= ui->le_ajout_commentaire->toPlainText();

    Produit p(Quantite,Prix,Dimensions,Poids,Volume,Categorie,Description,Reference,Emplacement,Date_de_creation,Date_d_expiration,Commentaire);


    QMessageBox msg;
    if(p.ajouterProduit())
    {
        //affectation de la matiere premiere
        for(int i=0;i<mp_a_affecte.size();i++)
        {
        if(!p.affecterMP(mp_a_affecte[i]))
        {
            QMessageBox msg;
            msg.setText("Erreur au niveau de l'affectation de la matiere premiere de ref :"+mp_a_affecte[i]+"!");
        }

        }
        msg.setText("ajout avec succés");
        show_tables(p.afficherProduit(),ui->tabProduits);
        ui->stackedWidget->setCurrentIndex(0);
        mp_a_affecte.clear();
        for(int i=0;i<num_row_mpAffecte.size();i++)
        {
           ui->tab_affectMP->showRow(num_row_mpAffecte[i]);

        }
        num_row_mpAffecte.clear();
    }
    else
    {
        msg.setText("echec lors de l'ajout");
    }
    msg.exec();


}

void MainWindow::on_button_okAjout_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);
    mp_a_affecte.clear();
    for(int i=0;i<num_row_mpAffecte.size();i++)
    {
       ui->tab_affectMP->showRow(num_row_mpAffecte[i]);

    }
    num_row_mpAffecte.clear();
}

void MainWindow::on_button_okModif_accepted()
{
    int Quantite=ui->le_modif_quantite->value();
    double Prix= ui->le_modif_prix->value();
    double Dimensions= ui->le_modif_dimensions->value();
    double Poids= ui->le_modif_poids->value();
    double Volume= ui->le_modif_volume->value();
    QString Categorie= ui->cb_modif_categorie->currentText();
    QString Description= ui->le_modif_description->text();
    QString Reference= ui->le_modif_reference->text();
    QString Emplacement= ui->le_modif_emplacement->text();
    QString Date_de_creation= ui->date_creation_modif->text();
    QString Date_d_expiration= ui->date_expiration_modif->text();
    QString Commentaire= ui->le_modif_commentaire->toPlainText();

    Produit p(Quantite,Prix,Dimensions,Poids,Volume,Categorie,Description,Reference,Emplacement,Date_de_creation,Date_d_expiration,Commentaire);

    bool test=p.modifierProduit();
    QMessageBox msg;
    if(test)
    {
        msg.setText("modifier avec succés");
        show_tables(p.afficherProduit(),ui->tabProduits);
         ui->stackedWidget->setCurrentIndex(0);
    }
    else
    {
        msg.setText("echec lors du modification");
    }
    msg.exec();

}

void MainWindow::on_button_okModif_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);
}



//Exporter en fichier Excel
void MainWindow::on_Button_exporterExcel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "produit", ui->tabProduits);

    //colums to export
    obj.addField(0, "CATEGORIE", "char(50)");
    obj.addField(1, "DESCRIPTION", "char(50)");
    obj.addField(2, "REFERENCE", "char(50)");
    obj.addField(3, "QUANTITE", "char(50)");
    obj.addField(4, "DATE_DE_CREATION", "char(50)");
    obj.addField(5, "DATE_D_EXPIRATION", "char(50)");
    obj.addField(6, "EMPLACEMENT", "char(50)");
    obj.addField(7, "PRIX", "char(50)");
    obj.addField(8, "DIMENSIONS", "char(50)");
    obj.addField(9, "POIDS", "char(50)");
    obj.addField(10, "VOLUME", "char(50)");
    obj.addField(11, "COMMENTAIRE", "char(50)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

//************************matiere premiere********************
//Ajout MP
void MainWindow::on_button_okAjoutMP_accepted()
{
    QString reference = ui->le_ajout_referenceMP->text();
    QString description = ui->le_ajout_descriptionMP->text();
    QString emplacement = ui->le_ajout_emplacementMP->text();
    int quantite = ui->sp_ajout_quantiteMP->value();
    double prix = ui->dsp_ajout_prixMP->value();
    QString dateAchat = ui->dateAchatMP_ajout->text();
    double poids = ui->dsp_ajout_poidsMP->value();
    double volume = ui->dsp_ajout_volumeMP->value();
    QString commentaire =ui->le_ajout_commentaireMP->toPlainText();

    MatierePremiere mp(reference,description,emplacement,quantite,prix,dateAchat,poids,volume,commentaire);
    mp.ajouterMP();
    show_tables(mp.afficherMP(),ui->tabMP);
    show_tables(mp.afficherMP(),ui->tab_affectMP);
    ui->stackedWidget_MP->setCurrentIndex(0);

}

//annuler ajout
void MainWindow::on_button_okAjoutMP_rejected()
{
    ui->stackedWidget_MP->setCurrentIndex(0);
}



void MainWindow::on_le_rechercheMP_textChanged()
{
    recherche(mp.afficherMP() ,ui->tabMP, ui->cb_coloneR_MP,ui->le_rechercheMP);

}

void MainWindow::on_Button_AjouterMP_clicked()
{
     ui->stackedWidget_MP->setCurrentIndex(1);
}

void MainWindow::on_Button_SupprimerMP_clicked()
{
    MatierePremiere mp;

    QMessageBox msgBox;
    QMessageBox msg;

    msgBox.setText("Voulez vous supprimer la matière première "
                   "de réference "+mpSelectionne+" ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int rep=msgBox.exec();
    switch(rep)
    {
          case QMessageBox::Yes:

            if(mp.supprimerMP(mpSelectionne))
            {
                msg.setText("Suppression avec succés");
                show_tables(mp.afficherMP(),ui->tabMP);
                show_tables(mp.afficherMP(),ui->tab_affectMP);
            }
            else
            {
                msg.setText("echec lors du suppression");
            }
            msg.exec();
                break;
          case QMessageBox::No:
            return;
                break;
    }
}

void MainWindow::on_tabMP_clicked(const QModelIndex &index)
{
    mpSelectionne=ui->tabMP->model()->data(index.sibling(index.row(),0)).toString();
}

void MainWindow::remplir_champsModifMP()
{
    //Remplir les champs
     QSqlQuery query;
    query.prepare("select * from MP where Reference= :refMP");
    query.bindValue(":refMP",mpSelectionne);
    if(query.exec())
    {
        while(query.next())
        {
            ui->le_modif_referenceMP->setText(query.value(0).toString());
            ui->le_modif_descriptionMP->setText(query.value(1).toString());
            ui->le_modif_emplacementMP->setText(query.value(2).toString());
            ui->sb_modif_quantiteMP->setValue(query.value(3).toInt());
            ui->dsb_modif_prixMP->setValue(query.value(4).toDouble());
            ui->dateAchatMP_modif->setDate(QDate::fromString(query.value(5).toString(),"dd/MM/yyyy"));
            ui->dsb_modif_poidsMP->setValue(query.value(6).toDouble());
            ui->dsb_modif_volumeMP->setValue(query.value(7).toDouble());
            ui->le_modif_commentaireMP->setPlainText(query.value(8).toString());

        }
    }

}
void MainWindow::on_tabMP_activated()
{
    ui->stackedWidget_MP->setCurrentIndex(2);
    remplir_champsModifMP();
}


void MainWindow::on_button_okAjoutMP_2_accepted()
{
    QString reference = ui->le_modif_referenceMP->text();
    QString description = ui->le_modif_descriptionMP->text();
    QString emplacement = ui->le_modif_emplacementMP->text();
    int quantite = ui->sb_modif_quantiteMP->value();
    double prix = ui->dsb_modif_prixMP->value();
    QString dateAchat = ui->dateAchatMP_modif->text();
    double poids = ui->dsb_modif_poidsMP->value();
    double volume = ui->dsb_modif_volumeMP->value();
    QString commentaire =ui->le_modif_commentaireMP->toPlainText();

    MatierePremiere mp(reference,description,emplacement,quantite,prix,dateAchat,poids,volume,commentaire);

    QMessageBox msgBox;
    QMessageBox msg;
        msgBox.setText("Voulez vous Enregistrer les modifications que vous avez apportées a la matière première "
                       "de réference "+reference+" ?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        int rep=msgBox.exec();

        switch(rep)
        {
              case QMessageBox::Save:
                    if(mp.modifierMP())
                    {
                        msg.setText("modifier avec succés");
                        show_tables(mp.afficherMP(),ui->tabMP);
                        show_tables(mp.afficherMP(),ui->tab_affectMP);
                        ui->stackedWidget_MP->setCurrentIndex(0);
                    }
                     else
                    {
                     msg.setText("echec lors du modification");
                    }
                    msg.exec();
                    break;

              case QMessageBox::Cancel:
                  return;
                  break;
        }

}

void MainWindow::on_button_okAjoutMP_2_rejected()
{
    ui->stackedWidget_MP->setCurrentIndex(0);

}

void MainWindow::on_Button_ExportMP_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "MP", ui->tabMP);

    //colums to export
    obj.addField(0, "REFERENCE", "char(50)");
    obj.addField(1, "DESCRIPTION", "char(50)");
    obj.addField(2, "EMPLACEMENT", "char(50)");
    obj.addField(3, "QUANTITE", "char(50)");
    obj.addField(4, "PRIX", "char(50)");
    obj.addField(5, "DATE_ACHAT", "char(50)");
    obj.addField(6, "POIDS", "char(50)");
    obj.addField(7, "VOLUME", "char(50)");
    obj.addField(8, "COMMENTAIRE", "char(50)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void MainWindow::on_le_rechercheMP_affecter_textChanged()
{
    recherche(mp.afficherMP() ,ui->tab_affectMP,ui->cb_coloneR_affectMP,ui->le_rechercheMP_affecter);
    //ne peux afficher les mp affectées
    for(int i=0;i<num_row_mpAffecte.size();i++)
    {
       ui->tab_affectMP->hideRow(num_row_mpAffecte[i]);
    }
}

void MainWindow::on_cb_coloneR_affectMP_currentIndexChanged(int index)
{
    recherche(mp.afficherMP() ,ui->tab_affectMP,ui->cb_coloneR_affectMP,ui->le_rechercheMP_affecter);
    //ne peux afficher les mp affectées
    for(int i=0;i<num_row_mpAffecte.size();i++)
    {
       ui->tab_affectMP->hideRow(num_row_mpAffecte[i]);

    }
}

void MainWindow::on_tab_affectMP_activated(const QModelIndex &index)
{
    //recuperer les mp à affecter
    QString mpSelec=ui->tab_affectMP->model()->data(index.sibling(index.row(),0)).toString();
    QMessageBox msgBox;
    msgBox.setText("Voulez vous affecter la matière première de réference "+mpSelec+" à ce produit?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int rep=msgBox.exec();

    switch(rep)
    {
          case QMessageBox::Yes:
    mp_a_affecte.push_back(mpSelec);
    num_row_mpAffecte.push_back(index.row());
    ui->tab_affectMP->hideRow(index.row());
            break;
        case QMessageBox::No:
        break;
    }

}

void MainWindow::on_tab_ref_mpAffecte_clicked(const QModelIndex &index)
{
    mpAffecte_selectionne=ui->tab_ref_mpAffecte->model()->data(index).toString();
}

void MainWindow::on_Button_desaffecterMP_clicked()
{
    Produit p;
    p.setReference(produitSelectionne);
    p.suppAffectation(mpAffecte_selectionne);
    ui->tab_ref_mpAffecte->setModel(p.afficher_MPaffecte());
}
