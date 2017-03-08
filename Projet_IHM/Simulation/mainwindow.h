#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "mainwindow.h"

namespace Ui {
class MainWindow;
}

namespace IdPorte {
    enum  enumId{Gauche , Droite};
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView* EauSaS;
    QLabel* BateauAmont;
    QLabel* BateauAvale;



public slots:
    void OuverturePorte (QGraphicsView *porte);
    void FermeturePorte(QGraphicsView* porte);
    void EauSASmonte();
    void EauSASdescend();
    void InitUi();
    void BateauAvanceAmont();
    void BateauAvanceAvale();
    void BateauMonter();
    void BateauDescente();
    void FeuVert(QLabel* vert , QLabel* rouge);
    void FeuRouge(QLabel* vert , QLabel* rouge);
    void Porte(QGraphicsView* porte, float value, IdPorte::enumId idporte);

    private slots:
    void on_pushButton1_clicked();
    void on_Etap2_clicked();
    void on_pushButton3_clicked();
    void on_Etape1_clicked();
    void on_Etape1_2_clicked();
    void on_Etape1_3_clicked();
};

#endif // MAINWINDOW_H

