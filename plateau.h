#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include <unordered_map>

#include "config/config.h"
#include "point.h"

class Plateau
{
    public:

    Plateau();
    //void afficher();
    int getCase(int x,int y) const;
    int getCase(Point coordonee) const;
    bool ajouterGeton(int x, int y, int valeur, bool coordoneeHumaine = false);
    bool ajouterGeton(Point coordonee, int valeur, bool coordoneeHumaine = false);
    bool peutEtreJouer(int x, int y) const;
    bool peutEtreJouer(Point coordonee) const;
    bool peutEtreJouer(int x, int y, int joueur) const;
    bool peutEtreJouer(Point coordonee, int joueur) const;
    bool peutJouer(int joueur) const;
    bool estPlein() const;
    void retourner(int x, int y, int joueur, bool newToken=true);
    void retourner(Point coordonee, int joueur, bool newToken=true);
    int getXmax() const;
    int getYmax() const;
    int nbrJetonsJoueur(int numJoueur) const;

    int simulationCoup(Point pointJouer, int joueur) const;
    bool isATokenReversed(Point playedPosition, int playerNumber) const;

    std::unordered_map<unsigned, Point> getPlayablePosition() const;

    Point examinerLigneDepuis(Point depart, int dx, int dy, int joueur) const;
    int examinerLigneDepuisNbrCase(Point depart, int dx, int dy, int joueur) const;
    void retournerLigne(Point depart, int dx, int dy, int nbrIteration);

    void jouerGeton(Point depart, int joueur);
    void jouerGeton(int x, int y, int joueur);

    static int switchPlayer(int playerNumber);

    private:

    std::unordered_map<unsigned, Point> playablePosition;
    int table[BOARD_SIZE_X][BOARD_SIZE_Y];
};

#endif // PLATEAU_H_INCLUDED
