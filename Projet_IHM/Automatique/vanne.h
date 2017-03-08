#ifndef VANNE_H
#define VANNE_H

#include <QThread>
#include <QBasicTimer>
#include "eau.h"
#include <QTimer>
#define CHECK_ALERT if(est_alerte){return;}

class Vanne : public QThread
{
    Q_OBJECT
    public:
        explicit Vanne(QObject *parent = 0);
        bool est_alerte;
        static Eau* _eau;

    public slots:
        void Ouverture();
        void FinOuverture();
        void FinFermeture();
        void Fermeture();
    protected slots:
        void run();
    private:
        QTimer Touverture;
        QTimer Tfermeture;

    signals:
        void VanneOuverte();
        void DebutOuverture();
        void VanneFermer();
        void DebutFermeture();

};

#endif // VANNE_H
