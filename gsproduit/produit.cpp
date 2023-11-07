#include "produit.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>//gerer les error
#include <string>
#include <QPdfWriter>//facilite la generation des document on format PDF
#include <QPainter>//creation de linterface graphique


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
          QSqlQuery query;
          QString qrcode_string=QString::number(qrcode);


               query.prepare("INSERT INTO GESTION_PRODUIT(QRCODE,NOM,CATEGORIE,QUANTITE)"
                             "VALUES (:QRCODE,:NOM,:CATEGORIE,:QUANTITE)");
               query.bindValue(":QRCODE",qrcode_string);
               query.bindValue(":NOM",nom);
               query.bindValue(":CATEGORIE",categorie);
               query.bindValue(":QUANTITE",quantite);


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
               query.prepare("UPDATE GESTION_PRODUIT SET NOM = COALESCE(:NOM, NOM), CATEGORIE = COALESCE(:CATEGORIE, CATEGORIE),QUANTITE = COALESCE(:QUANTITE, QUANTITE) WHERE QRCODE = :QRCODE");
               query.bindValue(":QRCODE", qrcode_string);
               query.bindValue(":NOM", nom.isEmpty() ? QVariant(QVariant::String) : nom);
               query.bindValue(":CATEGORIE", categorie.isEmpty() ? QVariant(QVariant::String) : categorie);
               query.bindValue(":QUANTITE", quantite.isEmpty() ? QVariant(QVariant::String) : quantite);


               return query.exec();
      }

