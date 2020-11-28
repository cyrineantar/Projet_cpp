#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include "reclamation.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_2->setModel(m.afficher());
    ui->tableView_3->setModel(r.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked() //ajouter machine
{
    QString code=ui->codemachine->text();
    QString date=ui->dateEditmachine->text();
    QString puissance=ui->puissancemachine->text();
    QString consommation=ui->consommationmachine->text();
    QString type=ui->typemachine->text();
 machine m(code,date,type,puissance,consommation);
 bool test=m.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
    ui->tableView_2->setModel(m.afficher());
 }
 else
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}

void MainWindow::on_pushButton_9_clicked() // supprimer machine
{
    machine m1;
    m1.setcode(ui->codemachineSuppr->text());
    bool test=m1.supprimer(m1.get_code());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tableView_2->setModel(m.afficher());
    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}
void MainWindow::on_addR_clicked()
{

    QString codeM=ui->codemachinerecl->text();
    QString date_panne=ui->date_panneEdit->text();
    QString cause_panne=ui->lineEdit_cause->text();
 reclamation r(cause_panne,date_panne,codeM);

 bool test=r.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
    ui->tableView_3->setModel(r.afficher());
 }
 else
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}




void MainWindow::on_DeleteR_clicked()
{
    reclamation r;
    r.setcodeM(ui->lineEdit_code_6->text());
    bool test=r.supprimer(r.get_codeM());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
      ui->tableView_3->setModel(r.afficher());
    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void MainWindow::on_modifierREC_clicked()
{
    QString codeM = ui->codemachinerecl_2->text();
    QString date_panne = ui->date_panneEdit_2->text();
    QString cause_panne = ui->lineEdit_cause_2->text();
    reclamation r(codeM, date_panne,cause_panne);
    bool test = r.modifier(codeM);
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Modification avec succes.");
        ui->modifierREC->setEnabled(false);
        ui->tableView_3->setModel(r.afficher());
    }
    else
    {
        msgBox.setText("Echec de modification");
    }
    msgBox.exec();
}
