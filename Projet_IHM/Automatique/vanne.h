#ifndef VANNE_H
#define VANNE_H

#include <QThread>

class Vanne : public QThread
{
    Q_OBJECT
    public:
        explicit Vanne(QObject *parent = 0);

    public slots:
        void Ouverture();
    protected slots:
        void run();

    signals:
        void VanneOuverte();
};

#endif // VANNE_H
