#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Retour_menu_3->setVisible(false);
    sonB= new QSound(":/sound/click.wav");

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{

   /* this->hide();
    stock s;
    s.setModal(true);
    s.exec();
    */

    // hide();
    sonB->play();
    s= new stock(this);
    s->show();


}

void MainWindow::on_b_espaceE_clicked()
{
    sonB->play();
    e= new espaceEmploye(this);
    e->show();
}

void MainWindow::on_b_espaceF_clicked()
{
    sonB->play();
    f= new Espace_fournisseur(this);
    f->show();
}


void MainWindow::on_b_espaceC_clicked()
{
    sonB->play();
    c= new Espace_client(this);
    c->show();

}

void MainWindow::on_b_espaceM_clicked()
{
    sonB->play();
    b= new espace_machine(this);
    b->show();
}

void MainWindow::on_b_espaceL_clicked()
{
    sonB->play();
    l= new Espace_livraison(this);
    l->show();

}

void MainWindow::on_connexion_clicked()
{
    sonB->play();
    QMessageBox msgBox;
    QString login,mdp;
    login=ui->le_login->text();
    mdp=ui->le_mdp->text();
    QSqlQuery query;
   query.prepare("select * from employe where nom=:login and mdp=:mdp");
   query.bindValue(":login",login);
   query.bindValue(":mdp",mdp);
   if(query.exec() && query.next())
   {   ui->Retour_menu_3->setVisible(true);
       QString fonction=query.value(7).toString().toUpper();
       if(fonction=="ADMINISTRATEUR")
       {
           ui->stackedWidget->setCurrentIndex(1);

       }
       else if(fonction=="EMPLOYE")
       {
           ui->stackedWidget->setCurrentIndex(2);

       }
       else if(fonction=="LIVREUR")
       {
           ui->stackedWidget->setCurrentIndex(3);

       }

   }
   else
   {
       msgBox.setText("login ou mot de passe incorect !");
       msgBox.setIcon(QMessageBox::Critical);
       msgBox.exec();

   }


}

void MainWindow::on_Retour_menu_3_clicked()
{
    sonB->play();
    ui->le_login->clear();
    ui->le_mdp->clear();
    ui->Retour_menu_3->setVisible(false);
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_b_espaceC_2_clicked()
{
    sonB->play();
    c= new Espace_client(this);
    c->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    sonB->play();
    s= new stock(this);
    s->show();

}

void MainWindow::on_b_espaceM_2_clicked()
{
    sonB->play();
    b= new espace_machine(this);
    b->show();
}

void MainWindow::on_b_espaceL_2_clicked()
{
    sonB->play();
    l= new Espace_livraison(this);
    l->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    sonB->play();
    s= new stock(this);
    s->show();

}

void MainWindow::on_b_espaceF_2_clicked()
{
    sonB->play();
    f= new Espace_fournisseur(this);
    f->show();
}
