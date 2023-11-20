#include "mdp.h"
#include "ui_mdp.h"
#include <QMessageBox>

mdp::mdp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mdp),
    loginWindow(nullptr)
{
    ui->setupUi(this);
}

mdp::~mdp()
{
    delete ui;
}

void mdp::on_pushButton_clicked()
{
        QString username = ui->le_name ->text();
        QString cin = ui->le_cin->text();
        if (verifierReponses(username, cin)) {
            QString code = recupererMotDePasse(username);
            QMessageBox::information(this, "Mot de passe récupéré", "Votre mot de passe est : " + code);
            this->show();
        } else {
            QMessageBox::critical(this, "Réponses incorrectes", "Les réponses fournies sont incorrectes !");
        }


}
////////////////////////////////////////////////////////////////////////////////////////
bool mdp::verifierReponses(const QString& nom, const QString& cin)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEE WHERE nom = :nom AND cin = :cin ");
    query.bindValue(":nom", nom);
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return true; // Réponses correctes
    } else {
        return false; // Réponses incorrectes
    }
}
///////////////////////////////////////////////////////////////////////////////////
QString mdp::recupererMotDePasse(const QString& nom)
{
    QSqlQuery query;
    query.prepare("SELECT code FROM EMPLOYEE WHERE nom = :nom");
    query.bindValue(":nom", nom);
    if (query.exec() && query.next()) {
        return query.value(0).toString(); // Récupérer le mot de passe
    } else {
        return ""; // En cas d'échec
    }
}
