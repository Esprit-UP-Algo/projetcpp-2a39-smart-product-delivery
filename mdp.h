#ifndef MDPOUB_H
#define MDPOUB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDialog>
#include "mainwindow.h"
#include "login.h"

namespace Ui {
class mdp;
}

class mdp : public QDialog
{
    Q_OBJECT

public:
    explicit mdp(QWidget *parent = nullptr);
    ~mdp();
    bool verifierReponses(const QString&, const QString& );
    QString recupererMotDePasse(const QString& );

private slots:
    void on_pushButton_clicked();

private:
    Ui::mdp *ui;
    login *loginWindow; // Assurez-vous d'avoir une référence vers la fenêtre de login
};

#endif // MDP_H
