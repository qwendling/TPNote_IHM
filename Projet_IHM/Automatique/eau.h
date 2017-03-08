#ifndef EAU_H
#define EAU_H

#include <QObject>
#include <QThread>
#include <QBasicTimer>
#include <QTimer>


class Eau : public QThread {
public:
    explicit Eau(QObject *parent = 0);
    //valeur entre 0 et 1 qui indique l'avancement de l'eau
    double avancement;
    QTimer Tavancement;

private:
    //Indique le pas de l'avancement de l'eau à chaque tick < 1
    double debit;
    // -debit si l'eau descend debit sinon
    double debitEffectif;

public slots:
    void Monter();
    void Descente();

signals:
    void estEnBas();
    void estEnHaut();

private slots:
    void Intermediaire();




};

#endif // EAU_H
