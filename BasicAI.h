#ifndef BASICAI_H
#define BASICAI_H

#include "GameAI.h"

#define COEF_LIGNEMOINS 4.1
#define COEF_LIGNEPLUS 5.1
#define COEF_COINMOINS 50.0
#define COEF_COINPLUS 1000.0
#define COEF_CASENONJOUABLE -3000.0

#define COEF_LIGNEPLUSRETOURNER 1.2
#define COEF_LIGNEPLUSSEUL 500.0

#define IA_DEBUTANT 0
#define IA_FACILE 1
#define IA_NORMALE 2

class BasicAI : public GameAI
{
public:
    BasicAI(unsigned playerNum, unsigned AIlevel = IA_NORMALE);

    Point play(const Plateau &position);

    int getNiveauIA() const;
    void setNiveauIA(int nivIA);

protected:
    double getScorePosition(const Plateau &position);

    double coefIAcase(int x, int y, const Plateau &position);
    double coefIAcase(int x, int y, const Plateau &position, int playerNum);
    double calculCoefCasePosition(int x, int y, const Plateau &position);
    double calculCoefCasePositionTourSuivant(int x, int y, const Plateau &position, int joueur);
    double simulationCoupCoef(int x,int y, const Plateau &position, int joueur);
    double simulationCoupCoef(Point pointJouer, const Plateau &position, int joueur);

protected:
    int niveauIA;

};

#endif // BASICAI_H
