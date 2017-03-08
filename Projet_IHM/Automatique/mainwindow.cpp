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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event){

    int id = event->timerId();
    if(id==milieu.timerId())
    {
        if(sens == true)
        {
            ui->Vert2->setVisible(true);
            ui->Rouge2->setVisible(false);
        }
        else
        {
            ui->Vert1->setVisible(true);
            ui->Rouge1->setVisible(false);
        }
        milieu.stop();
    }
    else if(id==general.timerId())
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
    ui->PorteDroite->setVisible(true);
    ui->PorteGauche->setVisible(true);
}

void MainWindow::light_init()
{
   ui->Rouge1->setVisible(true);
   ui->Rouge2->setVisible(true);
   ui->Vert1->setVisible(false);
   ui->Vert2->setVisible(false);
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

    milieu.start(10000,this);

}

void MainWindow::on_StopButton_clicked()
{
    //Fin des Timers
    porte1.stop();
    porte2.stop();
    milieu.stop();

    //Bloquage des boutons
    ui->Bateau1->setEnabled(false);
    ui->Bateau2->setEnabled(false);
    ui->BateauMilieu->setEnabled(false);

    //Affichage feu rouge
    ui->Rouge1->setVisible(true);
    ui->Rouge2->setVisible(true);

    ui->Vert1->setVisible(false);
    ui->Vert2->setVisible(false);
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
    snprintf(s,64,"avancement ouverture porte droite : %f /1",valeur);
    qDebug(s);
}

void MainWindow::AvancementPorteGauche(double valeur){
    char s[64];
    snprintf(s,64,"avancement ouverture porte gauche : %f /1",valeur);
    qDebug(s);
}

void MainWindow::PorteDouverte(){
    qDebug("Porte droite ouverte");
    //Affichage feu
    ui->Vert2->setVisible(true);
    ui->Rouge2->setVisible(false);

    //Affichage bateau mid
    ui->BateauMilieu->setVisible(!sens);
    ui->Bateau2->setVisible(sens);

    ui->PorteDroite->setVisible(false);
}

void MainWindow::PorteGouverte(){
    qDebug("Porte gauche ouverte");
    //Affichage feu
    ui->Vert1->setVisible(true);
    ui->Rouge1->setVisible(false);


    //Affichage bateau mid
    ui->BateauMilieu->setVisible(sens);
    ui->Bateau1->setVisible(!sens);

    ui->PorteGauche->setVisible(false);
}

void MainWindow::PorteGfermer(){
    qDebug("Porte gauche fermer");
    ui->PorteGauche->setVisible(true);
    porteDroite->DebutOuverture();
}

void MainWindow::PorteDfermer(){
    qDebug("Porte droit fermer");
    ui->PorteDroite->setVisible(true);
    porteGauche->DebutOuverture();
}
