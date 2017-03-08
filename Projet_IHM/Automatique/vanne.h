#ifndef VANNE_H
#define VANNE_H

#include <QThread>
#include <QBasicTimer>
#include <QTimer>
#define CHECK_ALERT if(!est_alerte){return;}

class Vanne : public QThread
{
    Q_OBJECT
    public:
        explicit Vanne(QObject *parent = 0);
        bool est_alerte;
    public slots:
        void Ouverture();
        void FinOuverture();
    protected slots:
        void run();
    private:
        QTimer Touverture;

    signals:
        void VanneOuverte();
        void DebutOuverture();
};

#endif // VANNE_H
