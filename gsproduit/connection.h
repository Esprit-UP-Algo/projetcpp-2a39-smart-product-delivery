#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    Connection();//Constructeur par defaut
    bool createconnect();
};

#endif // CONNECTION_H
