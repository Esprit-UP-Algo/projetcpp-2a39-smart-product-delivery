#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QCoreApplication>

#include <QSystemTrayIcon>
#include<QString>
class notification
{
public:
    notification();
    void notification_ajoutproduit();

    void notification_supprimerproduit();

    void notification_modifierproduit();

void notification_failed();


};



#endif // NOTIFICATION_H
