#include "employee.h"
#include "connection.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>

employee::employee()
{
    id=0 ; cin="" ; nom=""; prenom="";sexe="";date="";grade="";salaire="";email="";code="";

}
employee::employee(int id, QString cin,QString prenom ,QString nom,QString sexe,QString date ,QString grade,QString salaire ,QString email,QString code)
{
    this->id=id;
    this->cin=cin;
    this->prenom=prenom;
    this->nom=nom;
    this->sexe=sexe;
    this->date=date;
    this->grade=grade;
    this->salaire=salaire;
    this->email=email;
    this->code=code;
}
int employee :: getid()
{return id;}
QString employee ::getcin()
{return cin;}
QString employee ::getnom()
{return nom;}
QString employee ::getprenom()
{return prenom;}
QString employee ::getsexe()
{return sexe;}
QString employee ::getdate()
{return date;}
QString employee ::getgrade()
{return grade;}
QString employee ::getsalaire()
{return salaire;}
QString employee ::getemail()
{return email;}
QString employee ::getcode()
{return code;}

///////////////////////////////////////////////////
void employee ::setid(int id)
{this->id=id;}
void employee ::setcin(QString cin)
{this->cin=cin;}
void employee ::setnom(QString nom)
{this->nom=nom;}
void employee ::setprenom(QString prenom)
{this->prenom=prenom;}
void employee ::setsexe(QString sexe)
{this->sexe=sexe;}
void employee ::setdate(QString date)
{this->date=date;}
void employee ::setgrade(QString grade)
{this->grade=grade;}
void employee ::setsalaire(QString salaire)
{this->salaire=salaire;}
void employee ::setemail(QString email)
{this->email=email;}
void employee ::setcode(QString code)
{this->code=code;}

bool employee::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(id);

          query.prepare("INSERT INTO EMPLOYEE (ID, CIN, PRENOM, NOM , SEXE ,DATE_EMBOCHE,GRADE,SALAIRE,EMAIL,CODE) "
                        "VALUES (:id, :cin , :prenom, :nom, :date, :sexe , :grade, :salaire, :email, :code )");
          query.bindValue(0, id_string);
          query.bindValue(1, cin);
          query.bindValue(2, prenom);
          query.bindValue(3, nom);
          query.bindValue(4, sexe);
          query.bindValue(5, date);
          query.bindValue(6, grade);
          query.bindValue(7, salaire);
          query.bindValue(8, email);
          query.bindValue(9, code);

          return query.exec();
}
QSqlQueryModel * employee::affichier()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * from EMPLOYEE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_EMBOCHE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("GRADE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("SALAIRE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("CODE"));
    return model;
}
bool employee::supprimier(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("Delete from employee where ID = :id");
    query.bindValue(0,id_string);
    return query.exec();
}


bool employee::recherche_id(int id)
{
  QSqlQuery query;

  query.prepare("SELECT * FROM EMPLOYEE where ID= :id");
  query.bindValue(0,id);
  if (query.exec() && query.next())
  {
  return true;
  }
  else
  {
      return false;
  }
}
////////////////////////////////////////////////////////////////////////


QSqlQueryModel * employee::recherche(QString rech)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYEE WHERE NOM LIKE '%"+rech+"%' or Prenom LIKE '%"+rech+"%'  or CIN LIKE '%"+rech+"%' or GRADE LIKE '%"+rech+"%' or SEXE LIKE '%"+rech+"%' or DATE_EMBOCHE LIKE '%"+rech+"%' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_EMBOCHE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("GRADE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("SALAIRE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("CODE"));
    return model;
}



QSqlQueryModel * employee::tri_asc(int test)
{
    QSqlQueryModel * model=new QSqlQueryModel() ;
    QSqlQuery query ;
    if(test==1)
    {
        query.prepare("SELECT * FROM EMPLOYEE ORDER BY id ASC") ;
    }
    else if(test==2)
    {
        query.prepare("SELECT * FROM EMPLOYEE ORDER BY nom ASC") ;
    }
    else if(test==3)
    {
        query.prepare("SELECT * FROM EMPLOYEE ORDER BY prenom ASC") ;

    }
    if (query.lastError().isValid()) {
        qDebug() << query.lastError();
    }

    if (query.exec())
    {
        model->setQuery(query) ;
    }
    return model;
}

QSqlQueryModel * employee::tri_desc(int test)
{
    QSqlQueryModel * model=new QSqlQueryModel() ;
    QSqlQuery query ;
    if(test==1)
    {
        query.prepare("SELECT * FROM EMPLOYEE ORDER BY id DESC") ;
    }
    else if(test==2)
    {
        query.prepare("SELECT * FROM EMPLOYEE ORDER BY nom DESC") ;
    }
    else if(test==3)
    {
        query.prepare("SELECT * FROM EMPLOYEE ORDER BY prenom DESC") ;

    }
    if (query.lastError().isValid()) {
        qDebug() << query.lastError();
    }

    if (query.exec())
    {
        model->setQuery(query) ;
    }
    return model;
}
/////////////////////////////////////////////////////////////////////







