#ifndef ESPACE_MACHINE_H
#define ESPACE_MACHINE_H
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QComboBox>
#include <QSound>
#include <QMessageBox>
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
#include<QDesktopServices>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QSound>
#include "arduino.h"


#include <QDialog>
#include "machine.h"
#include "reclamation.h"

namespace Ui {
class espace_machine;
}

class espace_machine : public QDialog
{
    Q_OBJECT

public:
    explicit espace_machine(QWidget *parent = nullptr);
    ~espace_machine();
    void update_label();

private slots:

    void on_addR_clicked();

    void on_DeleteR_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_9_clicked();

    void on_modifierREC_clicked();

    void on_le_recherche_textChanged(const QString &arg1);

     void on_Trier_clicked();

     void on_PDF_clicked();

     void on_ModifierM_clicked();

     void on_le_recherche_2_textChanged(const QString &arg1);

     void on_Trier_recl_clicked();

     void on_pushButton_clicked();


     void on_pushButton_2_clicked();

     void on_export_excel_clicked();

private:
    Ui::espace_machine *ui;
    machine m;
    //reclamation r;
    QSortFilterProxyModel *proxy;
    QSound *clickSound;
    Arduino A;
    QByteArray data;

};

#endif // ESPACE_MACHINE_H
