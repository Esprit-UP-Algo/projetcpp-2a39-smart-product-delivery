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
#include "qrcode.h"
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

#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include "QPrintDialog"
#include "notifications.h"


#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    produit f;
      ui->affiche_tab->setModel(f.afficher());
 f.saveSqlQueryModelToPdf();

  ui->historique_view->setModel(f.afficher_his());
}

MainWindow::~MainWindow()
{
    delete ui;
    produit f;
      ui->affiche_tab->setModel(f.afficher());
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

      if (test){
          notification.notification_ajoutproduit();
          ui->qrcode->clear();
          ui->nom->clear();
          ui->categorie->clear();
          ui->quantite->clear();
      }

                  else{
           notification.notification_failed();
      }

 ui->historique_view->setModel(tr.afficher_his());
      ui->affiche_tab->setModel(f.afficher());


      tr.saveSqlQueryModelToPdf();
};
void MainWindow::on_afficher_clicked()
{
    produit f;
    ui->affiche_tab->setModel(f.afficher());
}
void MainWindow::on_supprimer_clicked() {
    produit f;
      QSqlQuery query1;
    int qrcode = ui->qrcode->text().toInt();
      query1.prepare("insert into HISTORIQUE (CODE_HISTORIQUE,ACTION,USER_HISTORIQUE)""values (:CODE_HISTORIQUE,'DELETE','ADMIN')");
     query1.bindValue(":CODE_HISTORIQUE", qrcode);
    bool test = f.supprimer(qrcode);
    if (test) {
         query1.exec();
  f.saveSqlQueryModelToPdf();
notification.notification_supprimerproduit();

    } else {

notification.notification_failed();

    }
    ui->affiche_tab->setModel(f.afficher());
 ui->historique_view->setModel(f.afficher_his());

}
bool produit::supprimer(int qrcode){


    produit f;
    QSqlQuery query,query1;


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
{  produit tr ;
        int qrcode=ui->qrcode->text().toInt();
           QString nom = ui->nom->text();
           QString categorie = ui->categorie->text();
           QString quantite = ui->quantite->text();

              produit f(qrcode,nom,categorie,quantite);
                 bool test=f.modifier(qrcode,nom,categorie,quantite);

                 if(test)
               {
                    f.saveSqlQueryModelToPdf();
  ui->affiche_tab->setModel(f.afficher());
 ui->historique_view->setModel(f.afficher_his());
notification.notification_modifierproduit();
               }
                 else
notification.notification_modifierproduit();

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

     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}
void MainWindow::on_rechercher_textChanged(const QString &arg1)
{

    produit f;
    int QRCODE= ui->rechercher->text().toInt();

  f.recherche(ui->affiche_tab,QRCODE);
    if (ui->rechercher->text().isEmpty())
    {
        ui->affiche_tab->setModel(f.afficher());
    }
}

void MainWindow::on_trier_clicked()
{
    produit f;
     ui->affiche_tab->setModel(f.trierqr());
}
void MainWindow::on_pdf_clicked()
{
    produit f;
    f.telechargerPDF();

             QMessageBox::information(nullptr,QObject::tr("OK"),
                        QObject::tr("TÃ©lÃ©chargement terminÃ©"), QMessageBox::Cancel);
}


void MainWindow::on_stat_clicked()
{

    QSqlQueryModel * model= new QSqlQueryModel();
   model->setQuery("select * from GESTION_PRODUIT where QUANTITE < 100 ");
   float M=model->rowCount();
   model->setQuery("select * from GESTION_PRODUIT where QUANTITE  between 100 and 250 ");
   float M1=model->rowCount();
   model->setQuery("select * from GESTION_PRODUIT where QUANTITE >250 ");
   float M2=model->rowCount();
   float total=M+M1+M2;
   QString a=QString("moins de 100 \t"+QString::number((M*100)/total,'f',2)+"%" );
   QString b=QString("entre 100 et 250 \t"+QString::number((M1*100)/total,'f',2)+"%" );
   QString c=QString("+250 \t"+QString::number((M2*100)/total,'f',2)+"%" );


   QPieSeries *series = new QPieSeries();
   QColor colorLessThan100(255, 170, 0);  // RGB(255, 170, 0) - Jaune orangé
   QColor colorBetween100And250(30, 15, 28);  // RGB(30, 15, 28) - Couleur personnalisée
   QColor colorGreaterThan250(128, 128, 128);  // RGB(128, 128, 128) - Gris

   series->append(a, M)->setBrush(colorLessThan100);
   series->append(b, M1)->setBrush(colorBetween100And250);
   series->append(c, M2)->setBrush(colorGreaterThan250);

   if (M != 0) {

       QPieSlice *slice = series->slices().at(0);
       slice->setLabelVisible();
       slice->setPen(QPen());
   }
   if (M1 != 0) {

       QPieSlice *slice1 = series->slices().at(1);
       slice1->setLabelVisible();
   }
   if (M2 != 0) {

       QPieSlice *slice6 = series->slices().at(2);
       slice6->setLabelVisible();
   }

   QChart *chart = new QChart();

   chart->addSeries(series);
   chart->setTitle("");
   chart->setBackgroundVisible(false);

   chart->setVisible(true);
   chart->legend()->setAlignment(Qt::AlignBottom);

   QChartView *chartView = new QChartView(chart);

   chartView->setRenderHint(QPainter::Antialiasing);
   QPalette pal = qApp->palette();


   chartView->resize(381, 331);

   chartView->setParent(ui->label_stat);
   chartView->show();


}


void MainWindow::on_qrcode_2_clicked()
{


        QString text ="Client details :"+ ui->affiche_tab->model()->data(ui->affiche_tab->model()->index(ui->affiche_tab->currentIndex().row(),0)).toString()
                                +" "+ui->affiche_tab->model()->data(ui->affiche_tab->model()->index(ui->affiche_tab->currentIndex().row(),1)).toString()
                                +" "+ui->affiche_tab->model()->data(ui->affiche_tab->model()->index(ui->affiche_tab->currentIndex().row(),2)).toString()
                                +" "+ui->affiche_tab->model()->data(ui->affiche_tab->model()->index(ui->affiche_tab->currentIndex().row(),3)).toString()
                                +" "+ui->affiche_tab->model()->data(ui->affiche_tab->model()->index(ui->affiche_tab->currentIndex().row(),4)).toString()
                                +" "+ui->affiche_tab->model()->data(ui->affiche_tab->model()->index(ui->affiche_tab->currentIndex().row(),5)).toString()
                                +" "+ui->affiche_tab->model()->data(ui->affiche_tab->model()->index(ui->affiche_tab->currentIndex().row(),6)).toString();
                        //text="user data";
                        using namespace qrcodegen;
                          // Create the QR Code object
                          QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                          qint32 sz = qr.getSize();
                          QImage im(sz,sz, QImage::Format_RGB32);
                            QRgb black = qRgb(  0,  0,  0);
                            QRgb white = qRgb(255,255,255);
                          for (int y = 0; y < sz; y++)
                            for (int x = 0; x < sz; x++)
                              im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                          ui->qr_code->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );


}




