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

//FICHIER A IMPORTE DANS AUTO






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

void MainWindow::FeuVert(QLabel* vert , QLabel* rouge)
{
    vert->setVisible(true);
    rouge->setVisible(false);
}

void MainWindow::FeuRouge(QLabel* vert , QLabel* rouge)
{
    rouge->setVisible(true);
    vert->setVisible(false);
}



//10 tick de fonction pour etre Ouverte ( correspond au temps voulu )
void MainWindow::OuverturePorte(QGraphicsView* porte){

    QRect geo_new = porte->geometry();

    geo_new.translate(0,-15);
    porte->setGeometry(geo_new);
}

//10 tick de fonction pour etre fermé ( correspond au temps voulu )
void MainWindow::FermeturePorte(QGraphicsView* porte){

    QRect geo_new = porte->geometry();

    geo_new.translate(0,15);
    porte->setGeometry(geo_new);
}


//8 tick de fonction pour que l'eau soit a niveau
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


//8 tick de fonction pour que l'eau soit a niveau
void MainWindow::EauSASdescend()
{
     QRect geo_new = EauSaS->geometry();

     //scale
     geo_new.setHeight(geo_new.height()-10);

     //geo_bateau.translate(0,+10);
     //translation parce que scale par rapport a en haut
     geo_new.translate(0,+10);
     EauSaS->setGeometry(geo_new);
}


//Appellé quand l'eau du SaS monte et que le bateau est dedans
void MainWindow::BateauMonter()
{
    QRect geo_new = BateauAvale->geometry();
    geo_new.translate(0,-10);
    BateauAvale->setGeometry(geo_new);
}

//Appellé quand l'eau du SaS descend et que le bateau est dedans
void MainWindow::BateauDescente()
{
    QRect geo_new = BateauAmont->geometry();
    geo_new.translate(0,+10);
    BateauAmont->setGeometry(geo_new);
}

//10 tick de fonction pour etre au SaS
void MainWindow::BateauAvanceAmont()
{
    QRect new_geo = BateauAmont->geometry();
    new_geo.translate(20,0);
    BateauAmont->setGeometry(new_geo);
}

//10 tick de fonction pour etre au SaS
void MainWindow::BateauAvanceAvale()
{
    QRect new_geo = BateauAvale->geometry();
    new_geo.translate(-20,0);
    BateauAvale->setGeometry(new_geo);
}



void MainWindow::Porte(QGraphicsView* porte , float value , MainWindow::IdPorte idporte)
{
    if(idporte == MainWindow::IdPorte::Gauche)
    {
        QRect geo_new = porte->geometry();
        geo_new.moveTop(80+(value*100));
        porte->setGeometry(geo_new);
    }
    else
    {
        QRect geo_new = porte->geometry();
        geo_new.moveTop(80+(value*120));
        porte->setGeometry(geo_new);
    }
}


//Bouton Test


void MainWindow::on_pushButton1_clicked()
{
    Porte(ui->Porte1 , 0 , MainWindow::IdPorte::Gauche);
}

void MainWindow::on_Etap2_clicked()
{
    Porte(ui->Porte1 , 0.5 , MainWindow::IdPorte::Gauche);
}

void MainWindow::on_pushButton3_clicked()
{
    Porte(ui->Porte1 , 1. , MainWindow::IdPorte::Gauche);
}

void MainWindow::on_Etape1_clicked()
{
    Porte(ui->Porte2 , 0 , MainWindow::IdPorte::Droite);
}

void MainWindow::on_Etape1_2_clicked()
{
     Porte(ui->Porte2 , 0.5 , MainWindow::IdPorte::Droite);
}

void MainWindow::on_Etape1_3_clicked()
{
    Porte(ui->Porte2 , 1. , MainWindow::IdPorte::Droite);
}
