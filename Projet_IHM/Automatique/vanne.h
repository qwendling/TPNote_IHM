#ifndef VANNE_H
#define VANNE_H

#include <QThread>

class Vanne : public QThread
{
    Q_OBJECT
public:
    explicit Vanne(QObject *parent = 0);
protected:
    void run();
    void Ouverture();
signals:
    void VanneOuverte();
};

#endif // VANNE_H
