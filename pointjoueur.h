#ifndef POINTJOUEUR_H
#define POINTJOUEUR_H

#include "point.h"

class PointJoueur : public Point
{
public:
    PointJoueur(int px, int py, int pjoueur);
    PointJoueur(Point point, int pjoueur);
    void setJoueur(int joueur);
    int getJoueur(int joueur);

private:
    int joueur;
};

#endif // POINTJOUEUR_H

