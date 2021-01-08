#ifndef ESPACE_CLIENT_H
#define ESPACE_CLIENT_H

#include <QDialog>
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

namespace Ui {
class Espace_client;
}

class Espace_client : public QDialog
{
    Q_OBJECT

public:
    explicit Espace_client(QWidget *parent = nullptr);
    ~Espace_client();
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
    Ui::Espace_client *ui;
    Client c;
    QString clientSelectionne;
    QSortFilterProxyModel *proxy;
    QSortFilterProxyModel *proxy_carteFid;
    CarteFidelite carte;
    int carteSelectionne;


};

#endif // ESPACE_CLIENT_H
