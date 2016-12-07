#ifndef GAMEAI_H
#define GAMEAI_H

#include "point.h"
#include "plateau.h"

class GameAI
{
public:
    GameAI(unsigned playerNum);

    virtual Point play(const Plateau &position) =0;

    int getPlayerNumber() const;
    void setPlayerNumber(int playerNum);

protected:
    virtual double getScorePosition(const Plateau &position) =0;

protected:
    int playerNumber;
};

#endif // GAMEAI_H
