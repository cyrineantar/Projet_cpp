#include "espace_machine.h"
#include "ui_espace_machine.h"



espace_machine::espace_machine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::espace_machine)
{
    reclamation r;
    ui->setupUi(this);
    ui->tableView_2->setModel(m.afficher());
    ui->tableView_3->setModel(r.afficher());

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
    clickSound=new QSound(":/sounds/click.wav");
    QSqlQuery query;
        query.prepare("SELECT CODE FROM machine");
        if(query.exec())
        {

                while(query.next())
                {
                    ui->codeMR->addItem(query.value(0).toString());
                }
        }
        ui->typemachine->addItem("SAVON");
        ui->typemachine->addItem("GEL");
        ui->typemachine->addItem("JAVEL");
        ui->typemachine->addItem("EMBALLAGE");

        ui->typemachine_2->addItem("SAVON");
        ui->typemachine_2->addItem("GEL");
        ui->typemachine_2->addItem("JAVEL");
        ui->typemachine_2->addItem("EMBALLAGE");


        if(query.exec())
        {

                while(query.next())
                {
                    ui->codeMd->addItem(query.value(0).toString());
                }
        }


        if(query.exec())
        {

                while(query.next())
                {
                    ui->codeMSUPPR->addItem(query.value(0).toString());
                }
        }


        if(query.exec())
        {

                while(query.next())
                {
                    ui->comboBox_3->addItem(query.value(0).toString());
                }
        }

        if(query.exec())
        {

                while(query.next())
                {
                    ui->comboBox_4->addItem(query.value(0).toString());
                }
        }

}

espace_machine::~espace_machine()
{
    delete ui;
}

void espace_machine::on_pushButton_3_clicked() //ajouter machine
{
    clickSound->play();
    QString code=ui->codemachine->text();
    QString date=ui->dateEditmachine->text();
    QString puissance=ui->puissancemachine->text();
    QString fonctionnement=ui->typemachine->currentText();
 machine m(code,date,fonctionnement,puissance);
 bool test=m.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
    ui->codeMR->addItem(code);
    ui->codeMd->addItem(code);
    ui->codeMSUPPR->addItem(code);
    ui->comboBox_3->addItem(code);
    ui->comboBox_4->addItem(code);
    ui->tableView_2->setModel(m.afficher());
 }
 else
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}

void espace_machine::on_pushButton_9_clicked() // supprimer machine
{
    clickSound->play();

    machine m1;
    m1.setcode(ui->codeMSUPPR->currentText());
    bool test=m1.supprimer(m1.get_code());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");

    ui->codeMd->removeItem(ui->codeMSUPPR->findText(ui->codeMSUPPR->currentText()));
    ui->comboBox_4->removeItem(ui->codeMSUPPR->currentIndex());
    ui->comboBox_3->removeItem(ui->codeMSUPPR->findText(ui->codeMSUPPR->currentText()));
    ui->codeMR->removeItem(ui->codeMSUPPR->findText(ui->codeMSUPPR->currentText()));
    ui->codeMSUPPR->removeItem(ui->codeMSUPPR->currentIndex());
    ui->tableView_2->setModel(m.afficher());

    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void espace_machine::on_ModifierM_clicked()  //modifier machine
{
    clickSound->play();
    QString code=ui->codeMd->currentText();
    QString date=ui->dateEditmachine_2->text();
    QString puissance=ui->puissancemachine_2->text();
    QString fonctionnement=ui->typemachine_2->currentText();
     machine m;
    bool test = m.modifier(code,date,fonctionnement,puissance);
    QMessageBox msgBox;

    if(test)
    {
        ui->tableView_2->setModel(m.afficher());
        msgBox.setText("Modification avec succes.");

    }
    else
    {
        msgBox.setText("Echec de modification");
    }
    msgBox.exec();
}

void espace_machine::on_le_recherche_2_textChanged(const QString &arg1)
{
    machine m;
        ui->tableView_2->setModel(m.rechercher(ui->cb_recherche_2->currentText(),arg1));
}

void espace_machine::on_Trier_clicked()
{
    clickSound->play();
    QString colone=ui->colone_tri->currentText();
    QString ordre=ui->ordre_tri->currentText();
    machine m;
    ui->tableView_2->setModel(m.tri(colone,ordre));
}


void espace_machine::on_addR_clicked()
{
    clickSound->play();
   reclamation r;
  r.setdate_panne(ui->date_panneEdit->text());
   r.setcause_panne(ui->lineEdit_cause->text());
  r.setcodeM(ui->codeMR->currentText());

 bool test=r.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
    ui->tableView_3->setModel(r.afficher());
    ui->comboBox_3->addItem(r.get_codeM());
    ui->comboBox_4->addItem(r.get_codeM());
 }
 else
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}




void espace_machine::on_DeleteR_clicked()
{
    clickSound->play();
    reclamation r;
    r.setcodeM(ui->codeMR->currentText());
    bool test=r.supprimer(r.get_codeM());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
      ui->tableView_3->setModel(r.afficher());
      ui->comboBox_4->removeItem(ui->comboBox_4->currentIndex());
      ui->comboBox_3->removeItem(ui->comboBox_4->findText(ui->comboBox_4->currentText()));
    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void espace_machine::on_modifierREC_clicked()
{
    clickSound->play();
    QString codeM = ui->comboBox_3->currentText();
    QString date_panne = ui->date_panneEdit_2->text();
    QString cause_panne = ui->lineEdit_cause_2->text();

    reclamation r;
    bool test = r.modifier(codeM,date_panne,cause_panne);
    QMessageBox msgBox;

    if(test)
    {
        ui->tableView_3->setModel(r.afficher());
        msgBox.setText("Modification avec succes.");


    }
    else
    {
        msgBox.setText("Echec de modification");
    }
    msgBox.exec();
}


void espace_machine::on_le_recherche_textChanged(const QString &arg1)
{
    reclamation r;
        ui->tableView_3->setModel(r.rechercher(ui->cb_recherche->currentText(),arg1));
}


void espace_machine::on_Trier_recl_clicked()
{
    clickSound->play();
    QString colone=ui->colone_tri_3->currentText();
    QString ordre=ui->ordre_tri_3->currentText();
    reclamation r;
    ui->tableView_3->setModel(r.tri(colone,ordre));
}



void espace_machine::on_PDF_clicked()
{
    clickSound->play();
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
                     "<center> <H1> Gestion machine </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

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



void espace_machine::update_label()
{
     data =A.read_from_arduino();
     QString DataAsString = QString(data);
         qDebug()<< data;
    if (data =="1")
    {ui->label->setText("alarme activée");
        ui->label_3->setText("alarm activée");}
    else if (data =="0")
    {ui->label->setText("alarme désactivée");
        ui->label_3->setText("alarme désactivée");}
}


void espace_machine::on_pushButton_clicked()
{
    A.write_to_arduino("0");
    qDebug() << "alarme désactivée" <<endl;

}

void espace_machine::on_pushButton_2_clicked()
{
    A.write_to_arduino("0");
    qDebug() << "alarme désactivée" <<endl;
}



void espace_machine::on_export_excel_clicked()
{
    QTableView *table;

                            table = ui->tableView_3;


                            QString filters("Excel Files (.xls)");

                            QString defaultFilter("Excel Files (*.xls)");

                            QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),

                                               filters, &defaultFilter);

                            QFile file(fileName);


                            QAbstractItemModel *model =  table->model();

                            if (file.open(QFile::WriteOnly | QFile::Truncate)) {

                                QTextStream data(&file);

                                QStringList strList;

                                for (int i = 0; i < model->columnCount(); i++) {

                                    if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)

                                        strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");

                                    else

                                        strList.append("");

                                }

                                data << strList.join(";") << "\n";

                                for (int i = 0; i < model->rowCount(); i++) {

                                    strList.clear();

                                    for (int j = 0; j < model->columnCount(); j++) {


                                        if (model->data(model->index(i, j)).toString().length() > 0)

                                            strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");

                                        else

                                            strList.append("");

                                    }

                                    data << strList.join(";") + "\n";

                                }

                                file.close();

                                QMessageBox::information(nullptr, QObject::tr("Export excel"),

                                                          QObject::tr("Export avec succes .\n"

                                                                      "Click OK to exit."), QMessageBox::Ok);
            }

}
