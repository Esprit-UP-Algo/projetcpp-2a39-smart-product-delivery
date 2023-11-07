#ifndef PRODUIT_H
#define PRODUIT_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQueryModel>
#include <QTableView>
class produit
{
public:
    //constructeurs
    produit();
          //Getters
         produit (int,QString,QString,QString);
         int getqrcode();

            QString getnom();
            QString getcategorie();
            QString getquantite();



             void setqrcode(int);
             void setnom(QString);
             void setcategorie(QString);
             void setquantite( QString);


            bool ajouter();
                   QSqlQueryModel* afficher();
                   bool supprimer(int);

                   bool modifier(int,QString,QString,QString);

private:
            int qrcode;
           QString  quantite,categorie,nom;


};

#endif // PRODUIT_H
