#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
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

public slots:

private slots:
    void on_Bateau2_clicked();
    void on_Bateau1_clicked();
    void on_BateauMilieu_clicked();
    void timerEvent(QTimerEvent *event);
    void light_init();
    void boat_init();
    void on_StopButton_clicked();
private:
    Ui::MainWindow *ui;

    //Timer porte
    QBasicTimer porte1;
    QBasicTimer porte2;
    QBasicTimer milieu;
    QBasicTimer general;

    //Sens ecluse  true->avale , false -> amont
    bool sens;

};

#endif // MAINWINDOW_H
