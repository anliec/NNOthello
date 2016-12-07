#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <string>
//#include <iostream>
//#include <vector>
#include <QApplication>
#include <QMainWindow>
#include "jeux.h"
#include "point.h"
#include "mygraphicsview.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QSizePolicy>

#define UI_MODE_DEBUG 1
#define UI_MODE_NORMALE 0

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
    void setModeToolBox(int mode);
    void afficherScore();
//    void setNiveauIA(int nivIA);
//    void setNiveauIANormale();
//    void setNiveauIAFacile();
//    void setNiveauIADebutant();
//    void setDebugMode();
    void setNormaleMode();

private:
    Ui::MainWindow *ui;
    MyGraphicsView *view;
    QPushButton *buttonJouerIA;
    QAction *AButtonJouerIA;
    QCheckBox *CBafficherCoef, *CBjeuxAutoIA;
    QAction *AcbAfficherCoef, *AcbJeuxAutoIA;

};

#endif // MAINWINDOW_H
