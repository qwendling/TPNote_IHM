#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLCDNumber>
#include <QDebug>
#include <QPixmap>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    vanneDroite(new Vanne),
    vanneGauche(new Vanne),
    porteDroite(new Porte),
    porteGauche(new Porte),
    _eau(new Eau)
{

    etatreset=false;
    ui->setupUi(this);
    ui->BordBas->setVisible(true);
    ui->BordBas->setEnabled(true);
    general.setSingleShot(true);
    QObject::connect(&general, SIGNAL(timeout()), this, SLOT(reset()));

    vanneDroite->start();
    vanneGauche->start();
    porteDroite->start();
    porteGauche->start();
    _eau->start();
    can_connect=false;
    ui->Mdp1->setVisible(can_connect);
    ui->Mdp2->setVisible(can_connect);

    QObject::connect(vanneDroite, SIGNAL(Alarme()), this, SLOT(AlarmeVD()));
    QObject::connect(vanneGauche, SIGNAL(Alarme()), this, SLOT(AlarmeVG()));
    QObject::connect(porteDroite, SIGNAL(Alarme()), this, SLOT(AlarmePD()));
    QObject::connect(porteGauche, SIGNAL(Alarme()), this, SLOT(AlarmePG()));

    //Binding des signaux associés aux vannes
    QObject::connect(vanneDroite, SIGNAL(VanneOuverte()), this, SLOT(VanneDroiteOuverte()));
    QObject::connect(vanneGauche, SIGNAL(VanneOuverte()), this, SLOT(VanneGaucheOuverte()));
    QObject::connect(vanneGauche, SIGNAL(DebutOuverture()), this, SLOT(DebutOuvertureG()));
    QObject::connect(vanneDroite, SIGNAL(DebutOuverture()), this, SLOT(DebutOuvertureD()));

    QObject::connect(vanneGauche, SIGNAL(DebutFermeture()), this, SLOT(DebutFermetureG()));
    QObject::connect(vanneDroite, SIGNAL(DebutFermeture()), this, SLOT(DebutFermetureD()));

    QObject::connect(vanneDroite, SIGNAL(VanneFermer()), this, SLOT(VanneDroiteFermer()));
    QObject::connect(vanneGauche, SIGNAL(VanneFermer()), this, SLOT(VanneGaucheFermer()));

    QObject::connect(this, SIGNAL(OuvrirVanneGauche()), vanneGauche, SLOT(Ouverture()));
    QObject::connect(this, SIGNAL(OuvrirVanneDroite()), vanneDroite, SLOT(Ouverture()));


    //Binding des signaux associé au portes
    QObject::connect(porteDroite, SIGNAL(Etat(double)), this, SLOT(AvancementPorteDroite(double)));
    QObject::connect(porteGauche, SIGNAL(Etat(double)), this, SLOT(AvancementPorteGauche(double)));
    QObject::connect(porteGauche, SIGNAL(Ouvert()), this, SLOT(PorteGouverte()));
    QObject::connect(porteDroite, SIGNAL(Ouvert()), this, SLOT(PorteDouverte()));
    QObject::connect(porteGauche, SIGNAL(Fermer()), this, SLOT(PorteGfermer()));
    QObject::connect(porteDroite, SIGNAL(Fermer()), this, SLOT(PorteDfermer()));

    //Binding des signaux pour eau
    QObject::connect(_eau, SIGNAL(Etat(double)) , this , SLOT(EauMD(double)));
    QObject::connect(_eau, SIGNAL(estEnHaut()) , this , SLOT(FiniMonter()));
    QObject::connect(_eau, SIGNAL(estEnBas()) , this , SLOT(FiniDesc()));

    //Init affichage
    ui->BateauMilieu->setVisible(false);
    light_init();

    EauSaS = ui->EauSas;
    BateauAmont = ui->BateauAmont;
    BateauAvale = ui->BateauAvale;
    InitUi();
    if(ui->APageInterface->currentIndex() == 0){
        mode=MANUELLE;
    }else{
        mode=AUTO;
    }
    ui->BtnFPam->setEnabled(false);
    ui->BtnOPam->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_ui(QPushButton* item){
    item->setVisible(true);
    item->setEnabled(true);
}

void MainWindow::boat_init()
{
    init_ui(ui->Bateau1);
    init_ui(ui->Bateau2);
    init_ui(ui->BateauMilieu);
    ui->BateauMilieu->setVisible(false);
}

void MainWindow::light_init()
{
   FeuRouge(ui->VertG,ui->RougeG);
   FeuRouge(ui->VertD,ui->RougeD);
   FeuRouge(ui->VertP1,ui->RougeP1);
   FeuRouge(ui->VertP2,ui->RougeP2);
   FeuRouge(ui->VertV1,ui->RougeV1);
   FeuRouge(ui->VertV2,ui->RougeV2);
}

void MainWindow::on_Bateau1_clicked()
{
    //general.stop();
    general.start(40000);

    //Affichage
    ui->Bateau2->setVisible(false);

    ui->Bateau1->setEnabled(false);

    emit OuvrirVanneGauche();

    //set sens
    sens = true ;
}

void MainWindow::on_Bateau2_clicked()
{
    general.start(40000);

    //Affichage
    ui->Bateau1->setVisible(false);

    ui->Bateau2->setEnabled(false);

    emit OuvrirVanneDroite();
    //set sens
    sens = false ;
}

void MainWindow::on_BateauMilieu_clicked()
{
    general.stop();
    general.start(40000);

    ui->BateauMilieu->setEnabled(false);

    FeuRouge(ui->VertD,ui->RougeD);
    FeuRouge(ui->VertG,ui->RougeG);
    FeuRouge(ui->VertP1,ui->RougeP1);
    FeuRouge(ui->VertP2,ui->RougeP2);

    if(sens){
        porteGauche->DebutFermeture();
    }else{
        porteDroite->DebutFermeture();
    }

}

void MainWindow::on_StopButton_clicked()
{
    general.stop();
    //Bloquage des boutons
    ui->Bateau1->setEnabled(false);
    ui->Bateau2->setEnabled(false);
    ui->BateauMilieu->setEnabled(false);

    //Affichage feu rouge
    ui->RougeG->setVisible(true);
    ui->RougeD->setVisible(true);

    ui->VertG->setVisible(false);
    ui->VertD->setVisible(false);
    porteDroite->TakeAlarme();
    porteGauche->TakeAlarme();
    vanneDroite->TakeAlarme();
    vanneGauche->TakeAlarme();
}


void MainWindow::OnAuthentifClicked(){
    can_connect=!can_connect;
    ui->Mdp1->setVisible(can_connect);
    ui->Mdp2->setVisible(can_connect);
}

void MainWindow::OnConnexionClicked(){
    //Mdp : ihmmdp
    QString s="ac525c20df8218b09888994085a165e2";
    if(s == QString(QCryptographicHash::hash((ui->Mdp2->property("text").toString().toUtf8()),QCryptographicHash::Md5).toHex())){
        if(ui->APageInterface->currentIndex() == 0){
            ui->APageInterface->setCurrentIndex(1);
            mode=AUTO;
        }else{
            ui->APageInterface->setCurrentIndex(0);
            mode=MANUELLE;
        }
    }
}

//BoutonManuelle

void MainWindow::DisableBtn(){
    ui->BtnFPam->setEnabled(false);
    ui->BtnFPav->setEnabled(false);
    ui->BtnFVam->setEnabled(false);
    ui->BtnFVav->setEnabled(false);
    ui->BtnOPam->setEnabled(false);
    ui->BtnOPav->setEnabled(false);
    ui->BtnOVam->setEnabled(false);
    ui->BtnOVav->setEnabled(false);
    ui->ButtonPam->setEnabled(false);
    ui->ButtonPav->setEnabled(false);
    ui->ButtonVam->setEnabled(false);
    ui->ButtonVav->setEnabled(false);
}


void MainWindow::on_BtnOVam_clicked()
{
    DisableBtn();
    vanneGauche->Ouverture();
}

void MainWindow::on_BtnFVam_clicked()
{
    DisableBtn();
    vanneGauche->Fermeture();
}

void MainWindow::on_BtnOPam_clicked()
{
    DisableBtn();
    porteGauche->DebutOuverture();
}



void MainWindow::on_BtnFPam_clicked()
{
    DisableBtn();
    FeuRouge(ui->VertP1,ui->RougeP1);
    porteGauche->DebutFermeture();
}



void MainWindow::on_BtnOVav_clicked()
{
    DisableBtn();
    vanneDroite->Ouverture();
}



void MainWindow::on_BtnFVav_clicked()
{
    DisableBtn();
    vanneDroite->Fermeture();
}




void MainWindow::on_BtnOPav_clicked()
{
    DisableBtn();
    porteDroite->DebutOuverture();
}



void MainWindow::on_BtnFPav_clicked()
{
    DisableBtn();
    FeuRouge(ui->VertP2,ui->RougeP2);
    porteDroite->DebutFermeture();
}



void MainWindow::on_BtnVertAm_clicked()
{
    FeuVert(ui->VertG,ui->RougeG);
    FeuVert(ui->VertP1,ui->RougeP1);
    FeuVert(ui->VertGM,ui->RougeGM);
}



void MainWindow::on_BtnRougeAm_clicked()
{
    FeuRouge(ui->VertG,ui->RougeG);
    FeuRouge(ui->VertP1,ui->RougeP1);
    FeuRouge(ui->VertGM,ui->RougeGM);
}


void MainWindow::on_BtnVertAv_clicked()
{
    FeuVert(ui->VertD,ui->RougeD);
    FeuVert(ui->VertP2,ui->RougeP2);
    FeuVert(ui->VertDM,ui->RougeDM);
}


void MainWindow::on_BtnRougeAv_clicked()
{
    FeuRouge(ui->VertD,ui->RougeD);
    FeuRouge(ui->VertP2,ui->RougeP2);
    FeuRouge(ui->VertDM,ui->RougeDM);
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->APageInterface->currentIndex() == 0){
        ui->APageInterface->setCurrentIndex(1);
        mode=AUTO;
    }else{
        ui->APageInterface->setCurrentIndex(0);
        mode=MANUELLE;
    }

}

void MainWindow::on_BugVam_clicked()
{
    vanneGauche->bug();
}

void MainWindow::on_BugPam_clicked()
{
    porteGauche->bug();
}

void MainWindow::on_BugPav_clicked()
{
    porteDroite->bug();
}

void MainWindow::on_BugVav_clicked()
{
    vanneDroite->bug();
}

void MainWindow::AlarmePG(){
    qDebug("Probleme Porte Gauche");
    ui->BtnFPam->setStyleSheet("background-color : red");
    ui->BtnOPam->setStyleSheet("background-color : red");
    on_StopButton_clicked();
}

void MainWindow::AlarmePD(){
    qDebug("Probleme Porte Droite");
    ui->BtnFPav->setStyleSheet("background-color : red");
    ui->BtnOPav->setStyleSheet("background-color : red");
    on_StopButton_clicked();
}

void MainWindow::AlarmeVD(){
    qDebug("Probleme Vanne Droite");
    ui->BtnFVav->setStyleSheet("background-color : red");
    ui->BtnOVav->setStyleSheet("background-color : red");
    on_StopButton_clicked();
}

void MainWindow::AlarmeVG(){
    qDebug("Probleme Vanne Gauche");
    ui->BtnFVam->setStyleSheet("background-color : red");
    ui->BtnOVam->setStyleSheet("background-color : red");
    on_StopButton_clicked();
}
