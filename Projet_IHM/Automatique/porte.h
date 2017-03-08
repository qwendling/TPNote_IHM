#ifndef PORTE_H
#define PORTE_H

#include <QObject>
#include <QThread>
#include <QBasicTimer>
#include <QTimer>

class Porte : public QThread
{
    Q_OBJECT
public:
    explicit Porte(QObject *parent = 0);
private:
    QTimer Touverture;
    //représente l'avancement 0=fermer 1=ouvert tout autre état est intermédiaire
    double Avancement;

public slots:
    void DebutOuverture();
    void EtapeOuverture();
signals:
    void Etat(double);
    void Ouvert();

};

#endif // PORTE_H
