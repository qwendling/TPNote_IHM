#include "porte.h"
#include "unistd.h"

Porte::Porte(QObject *parent) : QThread(parent){
    Avancement = 0;
    QObject::connect(&Touverture, SIGNAL(timeout()), this, SLOT(EtapeOuverture()));
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
