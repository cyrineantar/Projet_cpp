#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "machine.h"
#include "reclamation.h"

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

private:
    Ui::MainWindow *ui;
    machine m;
    reclamation r;
};
#endif // MAINWINDOW_H
