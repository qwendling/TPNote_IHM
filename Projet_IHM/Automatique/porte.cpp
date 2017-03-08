#include "porte.h"
#include "unistd.h"

Porte::Porte(QObject *parent) : QThread(parent){
    Avancement = 0;
    QObject::connect(&Touverture, SIGNAL(timeout()), this, SLOT(EtapeOuverture()));
    QObject::connect(&Tfermeture, SIGNAL(timeout()), this, SLOT(EtapeFermeture()));
    est_alerte=false;
}

void Porte::DebutOuverture(){
    CHECK_ALERT
    if(Avancement > 0.9){
        emit Ouvert();
        return;
    }
    Touverture.start(1000);
}

void Porte::EtapeOuverture(){
    CHECK_ALERT
    Avancement += 0.1;
    if(Avancement > 0.9){
        emit Ouvert();
        Touverture.stop();
    }
    emit Etat(Avancement);
}

void Porte::DebutFermeture(){
    CHECK_ALERT
    if(Avancement < 0.1){
        emit Fermer();
        return;
    }
    Tfermeture.start(1000);
}

void Porte::EtapeFermeture(){
    CHECK_ALERT
    Avancement -= 0.1;
    if(Avancement < 0.1){
        emit Fermer();
        Tfermeture.stop();
    }
    emit Etat(Avancement);
}
