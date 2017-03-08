#include "eau.h"
#include "unistd.h"

Eau::Eau(QObject *parent) : QThread(parent)
{
    this->start();
    QObject::connect(&Tavancement, SIGNAL(timeout()), this, SLOT(Intermediaire()));
    debit=0.1;
}

void Eau::Monter(){
    if(avancement >= 1){
        emit estEnHaut();
        return;
    }
    debitEffectif=debit;
    Tavancement.start(1000);
}

void Eau::Descente(){
    if(avancement <= 0){
        emit estEnBas();
        return;
    }
    debitEffectif=(-debit);
    Tavancement.start(1000);
}

void Eau::Intermediaire(){
    avancement += debitEffectif;
    if(avancement <= 0){
        avancement = 0;
        emit estEnBas();
        return;
    }
    if(avancement >= 1){
        avancement =1;
        emit estEnHaut();
        Tavancement.stop();
        return;
    }
}
