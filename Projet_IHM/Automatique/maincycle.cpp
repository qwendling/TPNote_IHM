#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLCDNumber>
#include <QDebug>
#include <QPixmap>


void MainWindow::reset()
{
    CHECK_mode(
    etatreset=true;
    nbreset=4;

    vanneDroite->Fermeture();
    vanneGauche->Fermeture();
    porteDroite-> DebutFermeture();
    porteGauche->DebutFermeture();

    ui->PorteDroite->setVisible(true);
    ui->PorteGauche->setVisible(true);
    light_init();
    boat_init();
    ui->Bateau1->setEnabled(false);
    ui->Bateau2->setEnabled(false);
    ,return;)
}



void MainWindow::DebutOuvertureG(){
    qDebug("Debut ouverture vanne Gauche");
}

void MainWindow::DebutOuvertureD(){
    qDebug("Debut ouverture vanne Droite");
}

void MainWindow::DebutFermetureG(){
    qDebug("Debut fermeture vanne Gauche");
}

void MainWindow::DebutFermetureD(){
    qDebug("Debut fermeture vanne Droite");
}

void MainWindow::VanneDroiteOuverte(){
    CHECK_mode(
    qDebug("Vanne droite ouverte");
    FeuVert(ui->VertV2 , ui->RougeV2);
    _eau->Descente();
    //§ Ajouter le bateau qui descend
    ,
    FeuVert(ui->VertV2 , ui->RougeV2);
    _eau->Descente();
    //ui->BtnFVav->setEnabled(true);
    //ui->BtnOVav->setEnabled(true);
    )
}

void MainWindow::VanneGaucheOuverte(){
    CHECK_mode(
    FeuVert(ui->VertV1 , ui->RougeV1);
    qDebug("Vanne gauche ouverte");
    _eau->Monter();
    ,
    FeuVert(ui->VertV1 , ui->RougeV1);
    _eau->Monter();
    //ui->BtnFVam->setEnabled(true);
    //ui->BtnOVam->setEnabled(true);
    )
}

void MainWindow::VanneGaucheFermer(){
    CHECK_mode(
    CHECK_RESET
    FeuRouge(ui->VertV1 , ui->RougeV1);
    qDebug("Vanne gauche fermer");
    vanneDroite->Ouverture();
    ,
    FeuRouge(ui->VertV1 , ui->RougeV1);
    if(_eau->avancement == 1)
    {
        ui->BtnFPam->setEnabled(true);
        ui->BtnOPam->setEnabled(true);
    }
    else{
    ui->BtnFPav->setEnabled(true);
    ui->BtnOPav->setEnabled(true);
    }
    )
}

void MainWindow::VanneDroiteFermer(){
    CHECK_mode(
    CHECK_RESET
    qDebug("Vanne droite fermer");
    FeuRouge(ui->VertV2 , ui->RougeV2);
    vanneGauche->Ouverture();
    ,
    FeuRouge(ui->VertV2 , ui->RougeV2);
    if(_eau->avancement == 0)
    {
        ui->BtnFPav->setEnabled(true);
        ui->BtnOPav->setEnabled(true);
    }
    else{
    ui->BtnOPam->setEnabled(true);
    ui->BtnFPam->setEnabled(true);
      }
    )
}

void MainWindow::AvancementPorteDroite(double valeur){
    char s[64];
    snprintf(s,64,"avancement porte droite : %f /1",valeur);
    PorteOF(ui->Porte2 , valeur , IdPorte::Droite);
    qDebug(s);
}

void MainWindow::AvancementPorteGauche(double valeur){
    char s[64];
    snprintf(s,64,"avancement porte gauche : %f /1",valeur);
    PorteOF(ui->Porte1 , valeur , IdPorte::Gauche);
    qDebug(s);
}

void MainWindow::PorteDouverte(){
    CHECK_mode(
    qDebug("Porte droite ouverte");
    //Affichage feu
    FeuVert(ui->VertD,ui->RougeD);
    FeuVert(ui->VertP2 , ui->RougeP2);


    //Affichage bateau mid
    ui->BateauMilieu->setVisible(!sens);
    ui->Bateau2->setVisible(sens);

    ui->PorteDroite->setVisible(false);

    if(sens == true)
        BateauAvanceAvale();
    else
        BateauAvanceAmont();

    ,
    FeuVert(ui->VertAv,ui->RougeAv);
    FeuVert(ui->VertP2 , ui->RougeP2);
    ui->BtnFPav->setEnabled(true);
    ui->BtnOPav->setEnabled(true);
    ui->BtnFVav->setEnabled(true);
    ui->BtnOVav->setEnabled(true);
    )
}

void MainWindow::PorteGouverte(){
    CHECK_mode(
    qDebug("Porte gauche ouverte");
    //Affichage feu
    FeuVert(ui->VertG,ui->RougeG);
    FeuVert(ui->VertP1 , ui->RougeP1);

    //Affichage bateau mid
    ui->BateauMilieu->setVisible(sens);
    ui->Bateau1->setVisible(!sens);

    ui->PorteGauche->setVisible(false);

    if(sens == true)
        BateauAvanceAmont();
    else
        BateauAvanceAvale();

    ,

    FeuVert(ui->VertAv,ui->RougeAv);
    FeuVert(ui->VertP2 , ui->RougeP2);
    ui->BtnOPam->setEnabled(true);
    ui->BtnFPam->setEnabled(true);
    ui->BtnOVam->setEnabled(true);
    ui->BtnFVam->setEnabled(true);
    )
}

void MainWindow::PorteGfermer(){
    CHECK_mode(
    CHECK_RESET
    qDebug("Porte gauche fermer");
    FeuRouge(ui->VertG,ui->RougeG);
    FeuRouge(ui->VertP1 , ui->RougeP1);

    ui->PorteGauche->setVisible(true);
    vanneGauche->Fermeture();
    ,
    if(_eau->avancement == 1)
    {
        ui->BtnOPam->setEnabled(true);
        ui->BtnFPam->setEnabled(true);
        ui->BtnFVam->setEnabled(true);
        ui->BtnOVam->setEnabled(true);
        ui->BtnFVav->setEnabled(true);
        ui->BtnOVav->setEnabled(true);
    }
    )
}

void MainWindow::PorteDfermer(){
    CHECK_mode(
    CHECK_RESET
    qDebug("Porte droit fermer");
    FeuRouge(ui->VertD,ui->RougeD);
    FeuRouge(ui->VertP2 , ui->RougeP2);

    ui->PorteDroite->setVisible(true);
    vanneDroite->Fermeture();
    ,
    if(_eau->avancement == 0)
    {
        ui->BtnOPav->setEnabled(true);
        ui->BtnFPav->setEnabled(true);
        ui->BtnFVav->setEnabled(true);
        ui->BtnOVav->setEnabled(true);
        ui->BtnFVam->setEnabled(true);
        ui->BtnOVam->setEnabled(true);
    })
}

void MainWindow::FiniMonter(){
    CHECK_mode(porteGauche->DebutOuverture();
                ,ui->BtnFVam->setEnabled(true);
    ui->BtnOVam->setEnabled(true);)
}

void MainWindow::FiniDesc(){
    CHECK_mode(porteDroite->DebutOuverture();
                ,ui->BtnFVav->setEnabled(true);
    ui->BtnOVav->setEnabled(true);)
}
