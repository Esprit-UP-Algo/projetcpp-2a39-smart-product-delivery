#include "produit.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>//gerer les error
#include <string>
#include <QPdfWriter>//facilite la generation des document on format PDF
#include <QPainter>//creation de linterface graphique
#include <QTextDocument>
#include <QFile>


#include <QSqlQueryModel>
#include <QTextDocument>
#include <QPdfWriter>
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QSqlError>

produit::produit()
{

        qrcode=0;
        categorie="";
        nom="";
       quantite="" ;
    }

    produit::produit(int qrcode,QString categorie,QString nom,QString quantite)
    {this-> qrcode= qrcode;this->categorie=categorie;this->nom=nom;this->quantite=quantite;}

    int produit::getqrcode(){return qrcode;}//obtenir les valeur de la variable

       QString produit::getcategorie(){return categorie;}

        QString produit::getnom(){return nom;}


        QString produit::getquantite(){return quantite;}

       void produit::setqrcode(int qrcode){this->qrcode=qrcode;}//mettre ajour la variable

       void produit::setcategorie(QString categorie){this->categorie=categorie;}

      void produit::setnom(QString nom){this->nom=nom;}

      void produit::setquantite(QString quantite){this->quantite=quantite;}


      bool produit::ajouter()
      {
          QSqlQuery query,query1;
          QString qrcode_string=QString::number(qrcode);

               query1.prepare("insert into HISTORIQUE (CODE_HISTORIQUE,ACTION,USER_HISTORIQUE)""values (:code_hist,'AJOUTER','ADMIN')");
               query.prepare("INSERT INTO GESTION_PRODUIT(QRCODE,NOM,CATEGORIE,QUANTITE)"
                             "VALUES (:QRCODE,:NOM,:CATEGORIE,:QUANTITE)");
               query.bindValue(":QRCODE",qrcode_string);
               query.bindValue(":NOM",nom);
               query.bindValue(":CATEGORIE",categorie);
               query.bindValue(":QUANTITE",quantite);

               query1.bindValue(":code_hist",qrcode_string);


              query1.exec();
               return query.exec();

      }
      QSqlQueryModel* produit::afficher()
      {
          QSqlQueryModel* model=new QSqlQueryModel();//read only DATAModel


                model->setQuery("SELECT* FROM GESTION_PRODUIT");//configurer le model pour executer une requete SQL

                model->setHeaderData(0, Qt::Horizontal, QObject::tr("QRCODE"));//configuration de l entete
                model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
                model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORIE"));
                model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));

         return model;
      };

      bool produit::modifier(int qrcode,QString nom,QString categorie,QString quantite)
      {

          QSqlQuery query1;
          QSqlQuery query;//xécuter des requêtes SQL
             query.prepare("SELECT COUNT(*) FROM GESTION_PRODUIT WHERE QRCODE = :QRCODE");//La requête SQL est destinée à compter le nombre d'enregistrements dans la table "GESTION_PRODUIT" qui ont le même QR code (qrcode)
               query.bindValue(":QRCODE", qrcode);
               query.exec();//La requête est exécutée
               query.next();//fournir des information
               int count = query.value(0).toInt();
               if (count == 0) {
                   return false;
               }

               QString qrcode_string = QString::number(qrcode);

               query1.prepare("insert into HISTORIQUE (CODE_HISTORIQUE,ACTION,USER_HISTORIQUE)""values (:CODE_HISTORIQUE,'UPDATE','ADMIN')");

               query.prepare("UPDATE GESTION_PRODUIT SET NOM = COALESCE(:NOM, NOM), CATEGORIE = COALESCE(:CATEGORIE, CATEGORIE),QUANTITE = COALESCE(:QUANTITE, QUANTITE) WHERE QRCODE = :QRCODE");
               query.bindValue(":QRCODE", qrcode_string);
               query.bindValue(":NOM", nom.isEmpty() ? QVariant(QVariant::String) : nom);
               query.bindValue(":CATEGORIE", categorie.isEmpty() ? QVariant(QVariant::String) : categorie);
               query.bindValue(":QUANTITE", quantite.isEmpty() ? QVariant(QVariant::String) : quantite);

               query1.bindValue(":CODE_HISTORIQUE",qrcode_string);
               query1.exec();

               return query.exec();
      }
      void produit::recherche(QTableView * affiche_tab ,int QRCODE )
      {
          QSqlQueryModel *model= new QSqlQueryModel();
          QString QRCODE_string=QString::number(QRCODE);
          QSqlQuery *query=new QSqlQuery;
          query->prepare("select * from GESTION_PRODUIT where QRCODE like '%"+QRCODE_string+"%';");
          query->exec();
          model->setQuery(*query);
          affiche_tab->setModel(model);
          affiche_tab->show();
      }

      QSqlQueryModel* produit::trierqr()
      {
          QSqlQueryModel * model=new QSqlQueryModel();
          model->setQuery("select * from GESTION_PRODUIT ORDER BY QRCODE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("QRCODE"));//configuration de l entete
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORIE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));

          return model;
      }
      void  produit::telechargerPDF(){

                           QPdfWriter pdf("C:/sarra/gestion_produits/pdf/fichier.pdf");
                           QPainter painter(&pdf);
                          int i = 4000;
                               painter.setPen(Qt::blue);
                               painter.setFont(QFont("Arial", 30));
                               painter.drawText(1100,1200,"GESTION_PRODUIT");
                               painter.setPen(Qt::black);
                               painter.setFont(QFont("Arial",14));
                               painter.drawRect(100,100,7300,2600);
                               painter.drawRect(0,3000,9600,500);
                               painter.setFont(QFont("Arial",8));
                               painter.drawText(300,3300,"QRCODE");
                               painter.drawText(1300,3300,"NOM");
                               painter.drawText(2200,3300,"CATEGORIE");
                               painter.drawText(3200,3300,"QUANTITE");



                               QSqlQuery query;

                               query.prepare("select * from GESTION_PRODUIT");
                               query.exec();
                               while (query.next())
                               {
                                   painter.drawText(300,i,query.value(0).toString());
                                   painter.drawText(1300,i,query.value(1).toString());
                                   painter.drawText(2300,i,query.value(2).toString());
                                   painter.drawText(3300,i,query.value(3).toString());




                                  i = i + 500;
                               }}

      QSqlQueryModel * produit::afficher_his()
          {
            QSqlQueryModel * model=new QSqlQueryModel();

            model->setQuery("select * from HISTORIQUE ORDER BY DATE_HISTORIQUE ");

             model->setHeaderData(0,Qt::Horizontal,QObject::tr("N°:"));
             model->setHeaderData(1,Qt::Horizontal,QObject::tr("ACTION :"));
             model->setHeaderData(2,Qt::Horizontal,QObject::tr("BY :"));
             model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE :"));

               return model;
          }
  void produit::saveSqlQueryModelToPdf()
      {
          QPdfWriter pdf("C:/sarra/gestion_produits/pdf/historique.pdf");

          QPainter painter(&pdf);
          int i = 4100;
         const QImage image(":/new/icons/icons/logo.png");
                      const QPoint imageCoordinates(155,0);
                      int width1 = 1600;
                      int height1 = 1600;
                      QImage img=image.scaled(width1,height1);
                      painter.drawImage(imageCoordinates, img );


                 QColor dateColor(0x4a5bcf);
                 painter.setPen(dateColor);

                 painter.setFont(QFont("Montserrat SemiBold", 11));
                 QDate cd = QDate::currentDate();
                 painter.drawText(8400,250,cd.toString("Tunis"));
                 painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                 QColor titleColor(0x341763);
                 painter.setPen(titleColor);
                 painter.setFont(QFont("Montserrat SemiBold", 25));

                 painter.drawText(3000,2700,"Liste des historique");

                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 //painter.drawRect(100,100,9400,2500);
                 painter.drawRect(100,3300,9400,500);

                 painter.setFont(QFont("Montserrat SemiBold", 10));

                 painter.drawText(500,3600,"N°:");
                 painter.drawText(2000,3600,"ACTION :");
                 painter.drawText(3300,3600,"BY :");
                 painter.drawText(5000,3600,"DATE :");


                 painter.setFont(QFont("Montserrat", 10));
                 painter.drawRect(100,3300,9400,9000);

                 QSqlQuery query;
                 query.prepare("select * from HISTORIQUE");
                 query.exec();
                 int y=4300;
                 while (query.next())
                 {
                     painter.drawLine(100,y,9490,y);
                     y+=500;
                     painter.drawText(500,i,query.value(0).toString());
                     painter.drawText(2000,i,query.value(1).toString());
                     painter.drawText(3300,i,query.value(2).toString());
                     painter.drawText(5000,i,query.value(3).toString());




                    i = i + 500;
                 }


      }
