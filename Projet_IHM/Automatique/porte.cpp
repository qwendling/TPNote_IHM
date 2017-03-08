#include "porte.h"
#include "unistd.h"

Porte::Porte(QObject *parent) : QThread(parent){
    Avancement = 0;
    QObject::connect(&Touverture, SIGNAL(timeout()), this, SLOT(EtapeOuverture()));
    QObject::connect(&Tfermeture, SIGNAL(timeout()), this, SLOT(EtapeFermeture()));
}

void Porte::DebutOuverture(){
    if(Avancement > 0.9){
        emit Ouvert();
        return;
    }
    Touverture.start(1000);
}

void Porte::EtapeOuverture(){
    Avancement += 0.1;
    if(Avancement > 0.9){
        emit Ouvert();
        Touverture.stop();
        return;
    }
    emit Etat(Avancement);
}

void Porte::DebutFermeture(){
    if(Avancement < 0.1){
        emit Fermer();
        return;
    }
    Tfermeture.start(1000);
}

void Porte::EtapeFermeture(){
    Avancement -= 0.1;
    if(Avancement < 0.1){
        emit Fermer();
        Tfermeture.stop();
        return;
    }
    emit Etat(Avancement);
}
