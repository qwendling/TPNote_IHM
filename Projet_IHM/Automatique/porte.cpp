#include "porte.h"
#include "unistd.h"

Porte::Porte(QObject *parent) : QThread(parent){
    Avancement = 0;
    QObject::connect(&Touverture, SIGNAL(timeout()), this, SLOT(EtapeOuverture()));
}

void Porte::DebutOuverture(){
    if((1-Avancement) < 0.00001){
        emit Ouvert();
    }
    Touverture.start(1000);
}

void Porte::EtapeOuverture(){
    Avancement += 1;
    if((1-Avancement) < 0.00001){
        emit Ouvert();
        Touverture.stop();
    }
    emit Etat(Avancement);
}
