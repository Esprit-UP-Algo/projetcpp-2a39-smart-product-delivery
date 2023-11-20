#ifndef LOGIN_H
#define LOGIN_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    bool verifierUtilisateur(const QString&, const QString&);

private slots:
    void on_pushButton_clicked();

    void on_yes_clicked();

private:
    Ui::login *ui;
    MainWindow *mainWindow;
};

#endif // LOGIN_H
