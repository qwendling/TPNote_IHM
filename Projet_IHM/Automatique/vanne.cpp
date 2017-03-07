#include "vanne.h"
#include "unistd.h"

Vanne::Vanne(QObject *parent) : QThread(parent){
    QObject::connect(&Touverture, SIGNAL(timeout()), this, SLOT(FinOuverture()));
    Touverture.setSingleShot(true);
}


void Vanne::run(){

}

void Vanne::Ouverture(){
    emit DebutOuverture();
    Touverture.start(1000);
}

void Vanne::FinOuverture(){
    emit VanneOuverte();
}
