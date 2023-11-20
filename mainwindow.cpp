#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include "connection.h"
#include <QObject>
#include <QMessageBox>
#include <QIntValidator>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id ->setValidator( new QIntValidator(0,99999999, this));//8 chiffre only
    ui->le_cin->setValidator( new QIntValidator(0,99999999, this));//8chifre only
    ui->tab_em->setModel(etmp.affichier());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_clicked()
{
    int id=ui->le_id ->text().toInt();
    QString cin=ui->le_cin  ->text();
    QString prenom=ui->le_prenom ->text();
    QString nom=ui->le_nom ->text();
    QString sexe=ui->le_sexe->text();
    QString date=ui->le_date  ->text();
    QString grade=ui->le_grade ->text();
    QString salaire=ui->le_salaire ->text();
    QString email=ui->email  ->text();
    QString code=ui->le_code->text();
    QDate dater = QDate::fromString(date, "yyyy/MM/dd");
        if (etmp.recherche_id(id))
        {
            QMessageBox::warning(this, QObject::tr("Duplicate ID"),QObject::tr("ID already exists. Please enter a unique ID."), QMessageBox::Cancel);
            return;
        }
        if (sexe != "homme" && sexe != "femme")
        {
                QMessageBox::warning(this, QObject::tr("Invalid Sexe"),QObject::tr("Please enter 'homme' or 'femme' for the Sexe field."), QMessageBox::Cancel);
                return;
        }
        if (grade != "pdg" && grade != "empjour" && grade != "empnuit")
        {
                QMessageBox::warning(this, QObject::tr("Invalid grade"),QObject::tr("Please enter the employee grade : 'pdg' or 'empjour' or 'empnuit' for the grade field."), QMessageBox::Cancel);
                return;
        }
        /*if (!dater.isValid())
        {
                QMessageBox::warning(this, QObject::tr("Invalid Date"),
                                     QObject::tr("Please enter a valid date."), QMessageBox::Cancel);
                return;
            }*/



    employee e(id,cin,prenom,nom,sexe,date,grade,salaire,email,code);
    bool test=e.ajouter();
    if (test)
    {
        QMessageBox::information(this, QObject::tr("ok"),
                    QObject::tr("ajout affecter.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_em->setModel(etmp.affichier());//mise a jour du tableau appres ajout
    }
    else
        QMessageBox::critical(this, QObject::tr("not ok"),
                    QObject::tr("ajout faild.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }


void MainWindow::on_pushButton_2_clicked()
{
    employee e1;
    e1.setid(ui->lineEdit_8->text().toInt());

    // Check if the ID exists
    if (e1.recherche_id(e1.getid())) {
        // ID exists, proceed with deletion
        bool test = e1.supprimier(e1.getid());

        if (test)
        {
            QMessageBox::information(this, QObject::tr("ok"),
                        QObject::tr("suppression effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

            ui->tab_em->setModel(etmp.affichier());//mise a jour du tableau après suppression
        }
        else {
            QMessageBox::critical(this, QObject::tr("not ok"),
                        QObject::tr("suppression failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    } else {
        // ID does not exist, show a message
        QMessageBox::warning(this, QObject::tr("ID not found"),
                    QObject::tr("The specified ID does not exist.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_clicked()
{

          int id=ui->le_id->text().toInt();
          QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirmation", "voulez vous modifier?",QMessageBox::Yes|QMessageBox::No);
                QString cin=ui->le_cin ->text();
                QString prenom=ui->le_prenom->text();
                QString nom=ui->le_nom ->text();
                QString sexe=ui->le_sexe->text();
                QString date=ui->le_date ->text();
                QString grade=ui->le_grade ->text();
                QString salaire=ui->le_salaire->text();
                QString email=ui->email ->text();
                QString code=ui->le_code ->text();
                QString id_string=QString::number(id);
                employee e(id,cin,prenom,nom,sexe,date,grade,salaire,email,code);

          QSqlQuery quer;
             quer.prepare("UPDATE EMPLOYEE SET CIN='"+cin+"', PRENOM='"+prenom+"', NOM='"+nom+"' , DATE_EMBOCHE='"+date+"', GRADE='"+grade+"' , salaire='"+salaire+"', EMAIL='"+email+"' , CODE='"+code+"' where  ID='"+id_string+"'");
           QMessageBox msgBox;
           if(quer.exec())
           {
           msgBox.setText("Modification avec succes.");
           ui->tab_em->setModel(etmp.affichier());

           }
           else
              {msgBox.setText("échec de modification");
                msgBox.exec();
}




        }










void MainWindow::on_afficher_clicked()
{

    int id;
    QString cin=ui->le_cin ->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString sexe=ui->le_sexe->text();
    QString date=ui->le_date ->text();
    QString grade=ui->le_grade ->text();
    QString salaire=ui->le_salaire->text();
    QString email=ui->email ->text();
    QString code=ui->le_code ->text();
    employee e(id,cin,prenom,nom,sexe,date,grade,salaire,email,code);
    ui->tab_em->setModel(etmp.affichier());

}

void MainWindow::on_clear_clicked()
{
     ui->le_id->clear();
     ui->le_cin->clear();
     ui->le_nom->clear();
     ui->le_prenom->clear();
     ui->le_sexe->clear();
     ui->le_date->clear();
     ui->le_grade->clear();
     ui->le_salaire->clear();
     ui->email->clear();
     ui->le_code->clear();


}

void MainWindow::on_tab_em_activated(const QModelIndex &index)
{
    QString val=ui->tab_em->model()->data(index).toString();
      QSqlQuery qry;
      qry.prepare("select * from EMPLOYEE where ID='"+val+"'");
      if(qry.exec())
      {
       while(qry.next())
       {
        ui->le_id->setText(qry.value(0).toString());
        ui->le_cin->setText(qry.value(1).toString());
        ui->le_prenom->setText(qry.value(2).toString());
        ui->le_nom->setText(qry.value(3).toString());
        ui->le_sexe->setText(qry.value(4).toString());
        ui->le_date->setText(qry.value(5).toString());
        ui->le_grade->setText(qry.value(6).toString());
        ui->le_salaire->setText(qry.value(7).toString());
        ui->email->setText(qry.value(8).toString());
        ui->le_code->setText(qry.value(9).toString());
       }
      }
      else
      {//qDebug()<<"Erreur  \n";
       QMessageBox::critical(this,tr("error::"),qry.lastError().text());
      }
}

void MainWindow::on_pushButton_trier_clicked()
{
    employee *emp = new employee();
        if (ui->radioButton ->isChecked()) {
            int triType = ui->comboBox_trier->currentIndex() + 1;
                QSqlQueryModel *model = emp->tri_asc(triType);
                ui->tableView_afficher->setModel(model);
        }
        if (ui->radioButton_2->isChecked()) {
            int triType = ui->comboBox_trier->currentIndex() + 1;
                QSqlQueryModel *model = emp->tri_desc(triType);
                ui->tableView_afficher->setModel(model);
        }
}

void MainWindow::on_pushButton_stat_clicked()
{
       QSqlQuery query;
       query.exec("SELECT sexe, COUNT(*) FROM EMPLOYEE GROUP BY sexe");

       QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
       while (query.next()) {
           QString sexe = query.value(0).toString();
           int count = query.value(1).toInt();
           QtCharts::QPieSlice * slice = new QtCharts::QPieSlice(sexe, count);
           series->append(slice);
       }

       QtCharts::QChart *chart = new QtCharts::QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques sur les sexe");
       chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

       QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setParent(ui->tableView_stats);
       chartView->resize(ui->tableView_stats->size());
       chartView->show();
}




/////////////////////////////////////////////////

void MainWindow::on_pushButton_PDF_clicked()
{

    QPdfWriter pdf("C:/pdf/list.pdf");

           QPainter painter(&pdf);
           int i = 4100;
           const QImage image("C:/pdf/logo.png");
                       const QPoint imageCoordinates(155,0);
                       int width1 = 2000;
                       int height1 = 2000;
                       QImage img=image.scaled(width1,height1);
                       painter.drawImage(imageCoordinates, img );


                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(7700,250,cd.toString("Ariana, El Ghazela"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste des employes");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));

                  painter.drawText(200,3600,"id");
                  painter.drawText(1000,3600,"cin");
                              painter.drawText(2000,3600,"Nom");
                              painter.drawText(3000,3600,"Prenom");
                              painter.drawText(4000,3600,"sexe");
                              painter.drawText(5000,3600,"date");
                              painter.drawText(6000,3600,"grade");
                              painter.drawText(7000,3600,"salaire");
                              painter.drawText(8000,3600,"email");
                              painter.drawText(9000,3600,"code");
                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from EMPLOYEE");
                  query.exec();
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                      painter.drawText(200,i,query.value(0).toString());
                      painter.drawText(1000,i,query.value(1).toString());
                          painter.drawText(2000,i,query.value(2).toString());
                          painter.drawText(3000,i,query.value(3).toString());
                          painter.drawText(4000,i,query.value(4).toString());
                          painter.drawText(5000,i,query.value(5).toString());
                          painter.drawText(6000,i,query.value(6).toString());
                          painter.drawText(7000,i,query.value(7).toString());
                          painter.drawText(8000,i,query.value(8).toString());
                          painter.drawText(9000,i,query.value(9).toString());


                     i = i + 500;
                  }

                  int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
                  if (reponse == QMessageBox::Yes)
                  {
                      QDesktopServices::openUrl( QUrl ::fromLocalFile("C:/pdf/list.pdf"));
                      painter.end();
                  }
                  else
                  {
                      painter.end();
                  }

}









void MainWindow::on_pushButton_cherche_clicked()
{
    QString searchTerm = ui->le_cherche->text().trimmed(); // Get and trim the input

    if (searchTerm.isEmpty()) {
        // Show a warning if the search term is empty
        QMessageBox::warning(this, "Empty Search Term", "Please enter a search term.", QMessageBox::Cancel);
        return; // Exit the function early
    }

    QSqlQueryModel *resultModel = etmp.recherche(searchTerm);

    if (resultModel) {
        ui->table_cher->setModel(resultModel);
    } else {
        qDebug() << "Search failed.";
    }
}

