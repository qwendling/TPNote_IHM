#include "vanne.h"
#include "unistd.h"

Eau* Vanne::_eau=new Eau();

Vanne::Vanne(QObject *parent) : QThread(parent){
    QObject::connect(&Touverture, SIGNAL(timeout()), this, SLOT(FinOuverture()));
    Touverture.setSingleShot(true);
    QObject::connect(&Tfermeture, SIGNAL(timeout()), this, SLOT(FinFermeture()));
    Tfermeture.setSingleShot(true);
    QObject::connect(_eau,SIGNAL(estEnBas()),this,SLOT(Ouverture()));
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
