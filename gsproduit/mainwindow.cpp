#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>//pouvoire ituliser les vecteur
#include <string>
#include <QBuffer>//utile pour gerer les donnees
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include<QDebug>
#include<QImage>
#include <QPixmap>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include<QTextDocument>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include "produit.h"
#include <QGraphicsView>
#include <QTabWidget>





#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked(){
    QString qrcode_string=ui->qrcode->text();
      bool ok;
      int qrcode=qrcode_string.toInt(&ok);
      if (!ok) {
          // Display error message for invalid input
          QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for qrcode.");
          return;
      }

      QString nom=ui->nom->text();
      QString categorie=ui->categorie->text();
      QString quantite=ui->quantite->text();



      produit tr(qrcode,nom,categorie,quantite);
      bool test = tr.ajouter();

      QMessageBox msgBox;
      if (test) {
          msgBox.setText("ajout avec succes");
          msgBox.exec();
          ui->qrcode->clear();
          ui->nom->clear();
          ui->categorie->clear();
          ui->quantite->clear();


      }
      else {
          msgBox.setText("echec");
          msgBox.exec();
      }

      ui->affiche_tab->setModel(tr.afficher());
};
void MainWindow::on_afficher_clicked()
{
    produit f;
    ui->affiche_tab->setModel(f.afficher());
}
void MainWindow::on_supprimer_clicked() {
    produit f;
    int qrcode = ui->qrcode->text().toInt();
    bool test = f.supprimer(qrcode);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                              QObject::tr("Échec de la suppression.\n"
                                          "Le produit n'existe pas dans la base de données."),
                              QMessageBox::Cancel);
    }
    ui->affiche_tab->setModel(f.afficher());


}
bool produit::supprimer(int qrcode){
    QSqlQuery query;
    QString res = QString::number(qrcode);
    query.prepare("DELETE FROM GESTION_PRODUIT WHERE QRCODE=:QRCODE");
    query.bindValue(":QRCODE", res);
    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;  // No rows were affected
    }
    return true;
}


/*void MainWindow::on_modifier_clicked()
{


            int qrcode=ui->qrcode->text().toInt();
               QString nom = ui->nom->text();
               QString categorie = ui->categorie->text();
               QString quantite = ui->quantite->text();

                  produit f(qrcode,nom,categorie,quantite);


                     bool test=f.modifier(qrcode,nom,categorie,quantite);

                     if(test)

                   {
                         ui->affiche_tab->setModel(f.afficher());

                   QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                     QObject::tr("invite modifiée.\n"

                                                 "Click ok to exit."), QMessageBox::Ok);

                   }

                     else


                         QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                     QObject::tr("echec d'ajout !.\n"

                                                 "Click Cancel to exit."), QMessageBox::Cancel);



}*/

void MainWindow::on_modifier_clicked()
{


    {


        int qrcode=ui->qrcode->text().toInt();
           QString nom = ui->nom->text();
           QString categorie = ui->categorie->text();
           QString quantite = ui->quantite->text();

              produit f(qrcode,nom,categorie,quantite);
                 bool test=f.modifier(qrcode,nom,categorie,quantite);

                 if(test)

               {ui->affiche_tab->setModel(f.afficher());

               QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                 QObject::tr("invite modifiée.\n"

                                             "Click ok to exit."), QMessageBox::Ok);
               }
                 else
                     QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                 QObject::tr("echec d'ajout !.\n"

                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_affiche_tab_activated(const QModelIndex &index)
{
    QString val=ui->affiche_tab->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from GESTION_PRODUIT where QRCODE='"+val+"'");
    if(qry.exec())
    {
     while(qry.next())
     {
      ui->qrcode->setText(qry.value(0).toString());
      ui->nom->setText(qry.value(1).toString());
      ui->categorie->setText(qry.value(2).toString());
      ui->quantite->setText(qry.value(3).toString());

     }
    }
    else
    {
        //qDebug()<<"Erreur  \n";
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

