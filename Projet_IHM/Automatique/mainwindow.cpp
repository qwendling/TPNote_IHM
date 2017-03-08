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
    porteGauche(new Porte)
{
    ui->setupUi(this);
    ui->BordBas->setVisible(true);
    ui->BordBas->setEnabled(true);

    //Binding des signaux associés aux vannes
    QObject::connect(vanneDroite, SIGNAL(VanneOuverte()), this, SLOT(VanneDroiteOuverte()));
    QObject::connect(vanneGauche, SIGNAL(VanneOuverte()), this, SLOT(VanneGaucheOuverte()));
    QObject::connect(vanneGauche, SIGNAL(DebutOuverture()), this, SLOT(DebutOuvertureG()));
    QObject::connect(vanneDroite, SIGNAL(DebutOuverture()), this, SLOT(DebutOuvertureD()));

    QObject::connect(this, SIGNAL(OuvrirVanneGauche()), vanneGauche, SLOT(Ouverture()));
    QObject::connect(this, SIGNAL(OuvrirVanneDroite()), vanneDroite, SLOT(Ouverture()));


    //Binding des signaux associé au portes
    QObject::connect(porteDroite, SIGNAL(Etat(double)), this, SLOT(AvancementPorteDroite(double)));
    QObject::connect(porteGauche, SIGNAL(Etat(double)), this, SLOT(AvancementPorteGauche(double)));
    QObject::connect(porteGauche, SIGNAL(Ouvert()), this, SLOT(PorteGouverte()));
    QObject::connect(porteDroite, SIGNAL(Ouvert()), this, SLOT(PorteDouverte()));
    QObject::connect(porteGauche, SIGNAL(Fermer()), this, SLOT(PorteGfermer()));
    QObject::connect(porteDroite, SIGNAL(Fermer()), this, SLOT(PorteDfermer()));


    vanneDroite->start();
    vanneGauche->start();
    porteDroite->start();
    porteGauche->start();
    //Init affichage
    ui->BateauMilieu->setVisible(false);
    light_init();

    EauSaS = ui->EauSas;
    BateauAmont = ui->BateauAmont;
    BateauAvale = ui->BateauAvale;
    InitUi();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event){

    int id = event->timerId();
    if(id==general.timerId())
    {
        light_init();
        boat_init();
        general.stop();
    }
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
    porteGauche->DebutFermeture();
    porteDroite->DebutFermeture();
}

void MainWindow::light_init()
{
   ui->RougeG->setVisible(true);
   ui->RougeD->setVisible(true);
   ui->VertG->setVisible(false);
   ui->VertD->setVisible(false);
}

void MainWindow::on_Bateau1_clicked()
{
    //Affichage
    ui->Bateau2->setVisible(false);

    //a faire avec sender
    ui->Bateau1->setEnabled(false);

    //Timer Lancement
    general.start(40000,this);

    emit OuvrirVanneGauche();

    //set sens
    sens = true ;
}

void MainWindow::on_Bateau2_clicked()
{
    //Affichage
    ui->Bateau1->setVisible(false);

    //a faire avec sender
    ui->Bateau2->setEnabled(false);

    //Timer Lancement
    general.start(30000,this);

    emit OuvrirVanneDroite();
    //set sens
    sens = false ;
}

void MainWindow::on_BateauMilieu_clicked()
{
    //a faire avec sender
    ui->BateauMilieu->setEnabled(false);

    light_init();

    if(sens){
        porteGauche->DebutFermeture();
    }else{
        porteDroite->DebutFermeture();
    }

}

void MainWindow::on_StopButton_clicked()
{

    //Bloquage des boutons
    ui->Bateau1->setEnabled(false);
    ui->Bateau2->setEnabled(false);
    ui->BateauMilieu->setEnabled(false);

    //Affichage feu rouge
    ui->RougeG->setVisible(true);
    ui->RougeD->setVisible(true);

    ui->VertG->setVisible(false);
    ui->VertD->setVisible(false);
}

void MainWindow::DebutOuvertureG(){
    qDebug("Debut ouverture vanne Gauche");
}

void MainWindow::DebutOuvertureD(){
    qDebug("Debut ouverture vanne Droite");
}

void MainWindow::VanneDroiteOuverte(){
    qDebug("Vanne droite ouverte");
    porteDroite->DebutOuverture();
}

void MainWindow::VanneGaucheOuverte(){
    qDebug("Vanne gauche ouverte");
    porteGauche->DebutOuverture();
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
    qDebug("Porte droite ouverte");
    //Affichage feu
    FeuVert(ui->VertD,ui->RougeD);
    FeuVert(ui->VertP2 , ui->RougeP2);


    //Affichage bateau mid
    ui->BateauMilieu->setVisible(!sens);
    ui->Bateau2->setVisible(sens);

    ui->PorteDroite->setVisible(false);
}

void MainWindow::PorteGouverte(){
    qDebug("Porte gauche ouverte");
    //Affichage feu
    FeuVert(ui->VertG,ui->RougeG);
    FeuVert(ui->VertP1 , ui->RougeP1);

    //Affichage bateau mid
    ui->BateauMilieu->setVisible(sens);
    ui->Bateau1->setVisible(!sens);

    ui->PorteGauche->setVisible(false);
}

void MainWindow::PorteGfermer(){
    qDebug("Porte gauche fermer");
    FeuRouge(ui->VertG,ui->RougeG);
    FeuRouge(ui->VertP1 , ui->RougeP1);

    ui->PorteGauche->setVisible(true);
    porteDroite->DebutOuverture();
}

void MainWindow::PorteDfermer(){
    qDebug("Porte droit fermer");
    FeuRouge(ui->VertD,ui->RougeD);
    FeuRouge(ui->VertP2 , ui->RougeP2);

    ui->PorteDroite->setVisible(true);
    porteGauche->DebutOuverture();
}



//Fonction de modification Simulation

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

void MainWindow::PorteOF(QGraphicsView* porte , float value , IdPorte::enumId idporte)
{
    if(idporte == IdPorte::Gauche)
    {
        QRect geo_new = porte->geometry();
        geo_new.moveTop(140+(value*100));
        porte->setGeometry(geo_new);
    }
    else
    {
        QRect geo_new = porte->geometry();
        geo_new.moveTop(140+(value*120));
        porte->setGeometry(geo_new);
    }
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
