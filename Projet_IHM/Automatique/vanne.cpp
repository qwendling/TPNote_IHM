#include "vanne.h"
#include "unistd.h"

Vanne::Vanne(QObject *parent) : QThread(parent){}


void Vanne::run(){

}

void Vanne::Ouverture(){
    emit VanneOuverte();
}
