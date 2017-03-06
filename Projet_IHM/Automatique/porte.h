#ifndef PORTE_H
#define PORTE_H

#include <QObject>
#include <QThread>
#include <QBasicTimer>
#include <QTimer>

class Porte
{
public:
    explicit Porte(QObject *parent = 0);
private:
    QBasicTimer Touverture;

};

#endif // PORTE_H
