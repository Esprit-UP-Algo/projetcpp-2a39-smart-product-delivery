#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QString>

class employee
{


public:
    employee();
    employee(int,QString,QString,QString,QString,QString,QString,QString,QString,QString);
    int getid();
    QString getcin();
    QString getnom();
    QString getprenom();
    QString getsexe();
    QString getdate();
    QString getgrade();
    QString getsalaire();
    QString getemail();
    QString getcode();
    void setid(int);
    void setcin(QString);
    void setnom(QString);
    void setprenom(QString);
    void setsexe(QString);
    void setdate(QString);
    void setgrade(QString);
    void setsalaire(QString);
    void setemail(QString);
    void setcode(QString);
    bool ajouter();
    QSqlQueryModel * affichier();
    bool supprimier(int);
    bool recherche_id(int);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * tri_asc(int);
    QSqlQueryModel * tri_desc(int);


private:
    int id;
    QString cin,nom,prenom,sexe,date,grade,salaire,email,code;

};

#endif // EMPLOYEE_H
