#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "vanne.h"
#include "porte.h"
#include "eau.h"
#include <QBasicTimer>
#include <QTimer>
#include <QCryptographicHash>
#define CHECK_RESET if(etatreset){\
if((--nbreset)<= 0)\
    etatreset = false;\
return;\
}
#define MANUELLE true
#define AUTO false

#define CHECK_mode(a,b) if(mode == AUTO){a}else{b}

namespace Ui {
class MainWindow;
}

namespace IdPorte {
    enum  enumId{Gauche , Droite};
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:

private slots:
    void on_Bateau2_clicked();
    void on_Bateau1_clicked();
    void on_BateauMilieu_clicked();
    //void timerEvent(QTimerEvent *event);
    void light_init();
    void boat_init();
    void on_StopButton_clicked();
    void init_ui(QPushButton* item);
    void VanneDroiteOuverte();
    void VanneGaucheOuverte();
    void VanneDroiteFermer();
    void VanneGaucheFermer();
    void DebutOuvertureG();
    void DebutOuvertureD();
    void DebutFermetureG();
    void DebutFermetureD();
    void AvancementPorteGauche(double);
    void AvancementPorteDroite(double);
    void PorteGouverte();
    void PorteDouverte();
    void PorteGfermer();
    void PorteDfermer();
    void reset();
    void DisableBtn();
    void FiniMonter();
    void FiniDesc();

    //Ajout fonction de simulation

    void EauMD(double value);
    void PorteOF(QGraphicsView* porte , float value , IdPorte::enumId idporte);
    void InitUi();
    void BateauAvanceAmont();
    void BateauAvanceAvale();
    void BateauMonter(QLabel* Bateau);
    void BateauDescente(QLabel* Bateau);
    void FeuVert(QLabel* vert , QLabel* rouge);
    void FeuRouge(QLabel* vert , QLabel* rouge);
    void OnAuthentifClicked();
    void OnConnexionClicked();

    //Bouton
    void on_BtnOVam_clicked();
    void on_BtnFVam_clicked();
    void on_BtnOPam_clicked();
    void on_BtnFPam_clicked();
    void on_BtnOVav_clicked();
    void on_BtnFVav_clicked();
    void on_BtnOPav_clicked();
    void on_BtnFPav_clicked();
    void on_BtnVertAm_clicked();
    void on_BtnRougeAm_clicked();
    void on_BtnVertAv_clicked();
    void on_BtnRougeAv_clicked();

    void on_pushButton_clicked();

signals:
    void OuvrirVanneGauche();
    void OuvrirVanneDroite();
private:

    bool etatreset;
    int nbreset;

    Ui::MainWindow *ui;
    Vanne* vanneDroite;
    Vanne* vanneGauche;
    Porte* porteGauche;
    Porte* porteDroite;
    Eau* _eau;
    bool can_connect;
    bool mode;

    //Timer porte
    QBasicTimer porte1;
    QBasicTimer porte2;
    QBasicTimer milieu;
    QTimer general;

    //Sens ecluse  true->avale , false -> amont
    bool sens;

    //Graphisme simulation
    QGraphicsView* EauSaS;
    QLabel* BateauAmont;
    QLabel* BateauAvale;

};

#endif // MAINWINDOW_H
