#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"

menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    MainWindow w;
    w.show();

}
