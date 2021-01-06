#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "client.h"
#include "cartefidelite.h"
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
#include <QSqlQuery>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void afficher_tabClient();
    void afficher_tab_carteFid();

private slots:
    void on_button_ajouterClient_clicked();

    void on_validerAjout_accepted();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_validerModif_accepted();

    void on_tabClient_clicked(const QModelIndex &index);

    void on_tabClient_activated();

    void on_validerAjout_rejected();

    void on_validerModif_rejected();

    void on_button_supprimerClient_clicked();

    void on_button_ajouter_carteFid_clicked();

    void on_validerAjout_cf_accepted();


    void on_le_recherche_carteFid_textChanged(const QString &arg1);

    void on_tabCarteFid_clicked(const QModelIndex &index);

    void on_tabCarteFid_activated();

    void on_button_supprimer_carteFid_clicked();

    void on_validerAjout_cf_rejected();

    void on_validerModif_cf_rejected();


    void on_validerModif_cf_accepted();

    void on_Button_pdf_clicked();

private:
    Ui::MainWindow *ui;
    Client c;
    QString clientSelectionne;
    QSortFilterProxyModel *proxy;
    QSortFilterProxyModel *proxy_carteFid;
    CarteFidelite carte;
    int carteSelectionne;

};
#endif // MAINWINDOW_H
