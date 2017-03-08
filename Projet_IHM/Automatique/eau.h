#ifndef EAU_H
#define EAU_H

#include <QObject>
#include <QThread>
#include <QBasicTimer>
#include <QTimer>


class Eau : public QThread {
public:
    explicit Eau(QObject *parent = 0);

};

#endif // EAU_H
