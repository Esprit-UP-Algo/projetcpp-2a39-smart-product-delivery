#include "login.h"
#include "ui_login.h"
#include "mdp.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login),
    mainWindow(nullptr)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    // Récupérer le nom d'utilisateur et le mot de passe saisis
    QString username = ui->lineeditnom->text();
    QString password = ui->lineEdit_mdp->text();

    // Vérifier le nom d'utilisateur et le mot de passe
    if (verifierUtilisateur(username, password)) {
        QString message = "Connexion réussie. Bienvenue " + username;
        QMessageBox::information(this, "Bienvenue", message);
        if (!mainWindow) {
            mainWindow = new MainWindow(this);
        }
        this->hide();
        mainWindow->show();
    } else {
        QMessageBox::critical(this, "Erreur de connexion", "Nom d'utilisateur ou mot de passe incorrect !");
    }
}

bool login::verifierUtilisateur(const QString &nom, const QString &code)
{

    // Préparer la requête SQL pour vérifier le nom d'utilisateur et le mot de passe
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEE WHERE NOM = :nom AND CODE = :code");
    query.bindValue(":nom", nom);
    query.bindValue(":code", code);

    // Exécuter la requête
    if (query.exec() && query.next()) {
        return true; // Nom d'utilisateur et mot de passe corrects
    } else {
        return false; // Nom d'utilisateur ou mot de passe incorrects
    }
}


void login::on_yes_clicked()
{
    mdp fenetreMotDePasseOublie;
    fenetreMotDePasseOublie.exec();
}
