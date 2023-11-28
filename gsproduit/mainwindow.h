#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "produit.h"
#include "notifications.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:

    void on_ajouter_clicked();
    void on_afficher_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_affiche_tab_activated(const QModelIndex &index);
    void on_rechercher_textChanged(const QString &arg1);


        void on_trier_clicked();
        void on_pdf_clicked();


        void on_stat_clicked();


        void on_qrcode_2_clicked();

        void on_pdf_2_clicked();

private:
    Ui::MainWindow *ui;
    produit f;
    notification notification;
};
#endif // MAINWINDOW_H
