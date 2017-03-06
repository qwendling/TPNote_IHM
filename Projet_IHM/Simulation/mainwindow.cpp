#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Init
    EauSaS = ui->EauSas;
    BateauAmont = ui->BateauAmont;
    BateauAvale = ui->BateauAvale;
    InitUi();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi()
{
    //Init Place
    BateauAmont->setGeometry(120,30,91,81);
    BateauAvale->setGeometry(540,110,91,81);

    //Cache
    BateauAmont->setVisible(false);
    BateauAvale->setVisible(false);
}

void MainWindow::OuverturePorte(QGraphicsView* porte){

    QRect geo_new = porte->geometry();

    geo_new.translate(0,-15);
    porte->setGeometry(geo_new);
}

void MainWindow::FermeturePorte(QGraphicsView* porte){

    QRect geo_new = porte->geometry();

    geo_new.translate(0,15);
    porte->setGeometry(geo_new);
}

void MainWindow::EauSASmonte()
{
     QRect geo_new = EauSaS->geometry();

    //QRect geo_bateau = bateau->geometry();
     //scale
     geo_new.setHeight(geo_new.height()+10);

     //geo_bateau.translate(0,-10);
     //translation parce que scale par rapport a en haut
     geo_new.translate(0,-10);
     EauSaS->setGeometry(geo_new);
}

void MainWindow::EauSASdescend()
{
     QRect geo_new = EauSaS->geometry();

     //QRect geo_bateau = bateau->geometry();

     //scale
     geo_new.setHeight(geo_new.height()-10);

     //geo_bateau.translate(0,+10);
     //translation parce que scale par rapport a en haut
     geo_new.translate(0,+10);
     EauSaS->setGeometry(geo_new);
}

void MainWindow::BateauAvanceAmont()
{
    QRect new_geo = BateauAmont->geometry();
    new_geo.translate(10,0);
    BateauAmont->setGeometry(new_geo);
}

void MainWindow::BateauAvanceAvale()
{
    QRect new_geo = BateauAvale->geometry();
    new_geo.translate(-10,0);
    BateauAvale->setGeometry(new_geo);
}


//Bouton Test

void MainWindow::on_Etap1_clicked()
{
    OuverturePorte(ui->Porte1);
}

void MainWindow::on_Etape1_clicked()
{
    OuverturePorte(ui->Porte2);
}

void MainWindow::on_Etap2_clicked()
{
    EauSASmonte();
}

void MainWindow::on_pushButton_clicked()
{
    EauSASdescend();
}

void MainWindow::on_pushButton_2_clicked()
{
    BateauAvale->setVisible(true);
    BateauAvanceAvale();
}

void MainWindow::on_pushButton_3_clicked()
{
    BateauAmont->setVisible(true);
    BateauAvanceAmont();
}
