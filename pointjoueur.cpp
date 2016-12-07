#include "pointjoueur.h"

PointJoueur::PointJoueur(int px, int py, int pjoueur) : Point(px,py)
{
    joueur = pjoueur;
}

PointJoueur::PointJoueur(Point point, int pjoueur) : Point(point.x,point.y)
{
    joueur = pjoueur;
}

void PointJoueur::setJoueur(int pjoueur){
    joueur = pjoueur;
}

int PointJoueur::getJoueur(int joueur){
    return joueur;
}
