#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "vanne.h"
#include "porte.h"
#include <QBasicTimer>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum  IdPorte{Gauche , Droite};

public slots:

private slots:
    void on_Bateau2_clicked();
    void on_Bateau1_clicked();
    void on_BateauMilieu_clicked();
    void timerEvent(QTimerEvent *event);
    void light_init();
    void boat_init();
    void on_StopButton_clicked();
    void init_ui(QPushButton* item);
    void VanneDroiteOuverte();
    void VanneGaucheOuverte();
    void DebutOuvertureG();
    void DebutOuvertureD();
    void AvancementPorteGauche(double);
    void AvancementPorteDroite(double);
    void PorteGouverte();
    void PorteDouverte();
    void PorteGfermer();
    void PorteDfermer();


    //Ajout fonction de simulation

    void PorteOF(QGraphicsView* porte , float value , MainWindow::IdPorte idporte);
    void EauSASmonte();
    void EauSASdescend();
    void InitUi();
    void BateauAvanceAmont();
    void BateauAvanceAvale();
    void BateauMonter();
    void BateauDescente();
    void FeuVert(QLabel* vert , QLabel* rouge);
    void FeuRouge(QLabel* vert , QLabel* rouge);

signals:
    void OuvrirVanneGauche();
    void OuvrirVanneDroite();
private:
    Ui::MainWindow *ui;
    Vanne* vanneDroite;
    Vanne* vanneGauche;
    Porte* porteGauche;
    Porte* porteDroite;

    //Timer porte
    QBasicTimer porte1;
    QBasicTimer porte2;
    QBasicTimer milieu;
    QBasicTimer general;

    //Sens ecluse  true->avale , false -> amont
    bool sens;

    //Graphisme simulation
    QGraphicsView* EauSaS;
    QLabel* BateauAmont;
    QLabel* BateauAvale;

};

#endif // MAINWINDOW_H
