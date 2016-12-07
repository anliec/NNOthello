#ifndef JEUX_H_INCLUDED
#define JEUX_H_INCLUDED

//#include <iterator>
#include <iostream>
#include <vector>
#include <memory>

#include <QApplication>
#include <QObject>
#include "plateau.h"
#include "point.h"
#include "pointjoueur.h"
#include "GameAI.h"


//#define NN_AI 1
//#define BASIC_AI 2

class Jeux : public QObject
{
    Q_OBJECT

public:

//    Jeux(Plateau table, int numJoueurIA, int typeIA=NN_AI, int niveauDeIA=2);
//    Jeux(int numJoueurIA=2);
    Jeux( std::shared_ptr<GameAI> AIplayer2 = std::shared_ptr<GameAI>(), std::shared_ptr<GameAI> AIplayer1 = std::shared_ptr<GameAI>());
    Jeux(const Plateau &table, std::shared_ptr<GameAI> AIplayer2 = std::shared_ptr<GameAI>(), std::shared_ptr<GameAI> AIplayer1 = std::shared_ptr<GameAI>());
    ~Jeux();
    //void jouer();
    void jouerUnJetons(int x,int y, int joueur); //pour la simulation de l'IA...
    void jouerIA();
    Point coupIA();
    Point coupIA(int IAtype, int joueur=2);

//    double coefIAcase(int x, int y, int joueur=2) const;
//    double calculCoefCasePosition(int x, int y) const;
//    double calculCoefCasePositionTourSuivant(int x, int y, int joueur) const;
//    double simulationCoupCoef(int x,int y, int joueur) const;
//    double simulationCoupCoef(Point pointJouer, int joueur) const;
    Plateau getPlateau() const;
//    int getNiveauIA() const;
//    void setNiveauIA(int nivIA);
    void setPlateau(Plateau table);
    void sauvgarderCoup(PointJoueur pointJ);
    void sauvgarderCoup(Point point, int joueur);
    void sauvgarderCoup(int x, int y, int joueur);
    void poserJeton(Point point, int joueur);
    void poserJeton(int x, int y, int joueur);

    bool estTerminee() const;

    //void boucleIA();

//    NeuralNetwork getNeuralNetwork();
//    void setNeuralNetwork(NeuralNetwork nn);


private:
    bool isAIplayer(int playerNumber) const;
    std::shared_ptr<GameAI> getAIplayer(int playerNumber) const;

public slots:
    bool jouer(int x, int y);
    bool jouer(Point P);
    void finDePartie();

signals:
    void partieFini();
    void partieFini(int gagnant);

private:

    Plateau plateau;
    //int joueurIA;
    int nbrTour;
    //int niveauIA;
    //bool IAapueJouer;
    bool partieTerminee;
    std::vector<PointJoueur> sav;
//    NeuralAI neuralAI;
//    int defaultAI;
    std::shared_ptr<GameAI> joueur1;
    std::shared_ptr<GameAI> joueur2;
    int currentPlayer;
};

#endif // JEUX_H_INCLUDED
