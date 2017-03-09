#include "vanne.h"
#include "unistd.h"


Vanne::Vanne(QObject *parent) : QThread(parent){
    QObject::connect(&Touverture, SIGNAL(timeout()), this, SLOT(FinOuverture()));
    Touverture.setSingleShot(true);
    QObject::connect(&Tfermeture, SIGNAL(timeout()), this, SLOT(FinFermeture()));
    Tfermeture.setSingleShot(true);
    est_alerte=false;
}


void Vanne::run(){

}

void Vanne::Ouverture(){
    CHECK_ALERT
    emit DebutOuverture();
    Touverture.start(1000);
}

void Vanne::FinOuverture(){
    CHECK_ALERT
    emit VanneOuverte();
}

void Vanne::Fermeture(){
    CHECK_ALERT
    emit DebutFermeture();
    Tfermeture.start(1000);
}

void Vanne::FinFermeture(){
    CHECK_ALERT
    emit VanneFermer();
}

void Vanne::TakeAlarme(){
    est_alerte=true;
    Tfermeture.stop();
    Touverture.stop();
}
