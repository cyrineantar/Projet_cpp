#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


      Connection c;
      bool test=c.createconnect();
      MainWindow w;
      QFile styleSheetFile(":/styleSheet/Integrid.qss");
          styleSheetFile.open(QFile::ReadOnly);
          QString styleSheet = QLatin1String(styleSheetFile.readAll());
          a.setStyleSheet(styleSheet);



    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("Rihem's database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("Rihem's database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
