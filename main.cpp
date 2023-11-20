#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include "connection.h"
#include "employee.h"
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    login lg;
    Connection c;
    bool test=c.createconnect();
    if(test)
    {
        lg.show();
        //w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
