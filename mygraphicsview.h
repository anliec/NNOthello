#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QMessageBox>

//#include <iterator>
//#include <iostream>

#include "jeux.h"

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
    public:
        explicit MyGraphicsView(QWidget *parent = 0);
        int nbrJetons(int numJoueur);

    signals:
        void sendMousePoint(QPointF point);

    public slots:
        void mousePressEvent(QMouseEvent * e);
        //int heightForWidth( int w );
        void resizeEvent(QResizeEvent * event);
        void actualiserAffichage();
        void actualiserTailleCase();
//        void setAfficherCoefIA(bool afficher);
//        void faireJouerIA();
//        void setModeJeuxIA(int mode);
        void finDePartie();
        void finDePartie(int vainceur);
//        void setNiveauIA(int nivIA);
        void nouvellePartie();

    signals:
        void aChanger();
        void finDuJeux();

    private:
           QGraphicsScene * scene;
           Jeux *jeux;
           QBrush brushJ1, brushJ2/*, brushJ0*/;
           QPen penJ1, penJ2/*, penJ0*/;
           int a, b; //a: taille carreau en x //b: en y
           //bool afficherCoefIA;
           //int modeJeuxIA;
           QMessageBox *messageBoxFinPArtie;
};

#endif // MYGRAPHICSVIEW_H
