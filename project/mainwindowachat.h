#ifndef MAINWINDOWACHAT_H
#define MAINWINDOWACHAT_H

#include <QMainWindow>
#include"achat.h"
#include  <QSound>
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindowAchat;
}
QT_END_NAMESPACE

class MainWindowAchat : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowAchat(QWidget *parent = nullptr);
    ~MainWindowAchat();

private slots:


    void on_pb_ajoutercommande_clicked();

    void on_pb_supprimer_2_clicked();

    void on_le_recherche_2_textChanged(const QString &arg1);

    void on_tabachat_clicked(const QModelIndex &index);

    void on_pb_modifier_5_clicked();

    void on_tabachat_activated();

    void on_tri_clicked();

    void on_pushButton_clicked();

    void on_PDF_clicked();

private:
    Ui::MainWindowAchat *ui;
      QSound *son;
      int achatselect;
      achat a;
};

#endif // MAINWINDOWACHAT_H
