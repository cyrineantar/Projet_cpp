#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "machine.h"
#include "reclamation.h"
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QComboBox>
#include <QSound>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    machine m;
    reclamation r;
    QSortFilterProxyModel *proxy;
    QSound *clickSound;

};
#endif // MAINWINDOW_H
