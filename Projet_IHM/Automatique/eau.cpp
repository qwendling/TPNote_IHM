#include "eau.h"
#include "unistd.h"

Eau::Eau(QObject *parent) : QThread(parent)
{
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
    char s[128];
    snprintf(s,128,"%lf",avancement);
    qDebug(s);
    emit Etat(avancement);
    if(avancement < (-debitEffectif)){
        avancement = 0;
        emit estEnBas();
        Tavancement.stop();
        return;
    }
    if(avancement > 1-debitEffectif){
        avancement =1;
        emit estEnHaut();
        Tavancement.stop();
        return;
    }
}
