#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLCDNumber>
#include <QDebug>
#include <QPixmap>

//Fonction de modification Simulation

void MainWindow::InitUi()
{

    //Cache
    BateauAmont->setVisible(true);
    BateauAvale->setVisible(true);
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


void MainWindow::PorteOF(QGraphicsView* porte , float value , IdPorte::enumId idporte)
{
    if(idporte == IdPorte::Gauche)
    {
        QRect geo_new = porte->geometry();
        geo_new.moveTop(140+(value*100));
        porte->setGeometry(geo_new);
        ui->BarGauche->setValue(value*100);
    }
    else
    {
        QRect geo_new = porte->geometry();
        geo_new.moveTop(140+(value*120));
        porte->setGeometry(geo_new);
        ui->BarDroite->setValue(value*100);
    }
}

void MainWindow::EauMD(double value)
{
    QRect geo_new = EauSaS->geometry();


    geo_new.setTop(250-(value*80));
    EauSaS->setGeometry(geo_new);
}



//Appellé quand l'eau du SaS monte et que le bateau est dedans
void MainWindow::BateauMonter(QLabel* Bateau)
{
    QRect geo_new = Bateau->geometry();
    geo_new.translate(0,-10);
    Bateau->setGeometry(geo_new);
}

//Appellé quand l'eau du SaS descend et que le bateau est dedans
void MainWindow::BateauDescente(QLabel* Bateau)
{
    QRect geo_new = Bateau->geometry();
    geo_new.translate(0,+10);
    Bateau->setGeometry(geo_new);
}

//10 tick de fonction pour etre au SaS
void MainWindow::BateauAvanceAmont()
{

    QRect new_geo = BateauAmont->geometry();
    new_geo.translate(200,0);
    BateauAmont->setGeometry(new_geo);
}

//10 tick de fonction pour etre au SaS
void MainWindow::BateauAvanceAvale()
{
    QRect new_geo = BateauAvale->geometry();
    new_geo.translate(-200,0);
    BateauAvale->setGeometry(new_geo);
}
