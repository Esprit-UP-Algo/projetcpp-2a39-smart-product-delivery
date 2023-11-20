#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employee.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_clicked();
    void on_pushButton_2_clicked();

    void on_modifier_clicked();

    void on_afficher_clicked();

    void on_clear_clicked();

    void on_tab_em_activated(const QModelIndex &index);

    void on_pushButton_trier_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_PDF_clicked();

    void on_pushButton_cherche_clicked();

private:
    Ui::MainWindow *ui;
    employee etmp;

};

#endif // MAINWINDOW_H
