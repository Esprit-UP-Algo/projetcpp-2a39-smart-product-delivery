#include "notifications.h"
#include "QApplication"
#include <QSystemTrayIcon>
#include<QString>
notification::notification()
{

}
void notification::notification_ajoutproduit()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   notifyIcon->setIcon(QIcon(":/new/prefix1/icon_valide.png"));
   notifyIcon->show();
    notifyIcon->showMessage("Gestion des Produit ","nouveau Produit est ajouté ",QSystemTrayIcon::Information,15000);
    srand (time(NULL));
}

void notification::notification_supprimerproduit(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

 notifyIcon->setIcon(QIcon(":/new/prefix1/icon_valide.png"));
   notifyIcon->show();
    notifyIcon->showMessage("Gestion des Produit","Produit est supprimé",QSystemTrayIcon::Information,15000);
srand (time(NULL));
}


void notification::notification_modifierproduit(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   notifyIcon->setIcon(QIcon(":/new/prefix1/icon_valide.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Produit ","Produit est modifié",QSystemTrayIcon::Information,15000);
srand (time(NULL));
}


void notification::notification_failed(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   //notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Produit ","action failed",QSystemTrayIcon::Critical,15000);
srand (time(NULL));
}



















