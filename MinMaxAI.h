#ifndef MINMAXAI_H
#define MINMAXAI_H

#include "GameAI.h"

class MinMaxAI : public GameAI
{
public:
    MinMaxAI(unsigned playerNumber, unsigned explorationDepth);

    virtual Point play(const Plateau &position);

protected:
    virtual double getBestScorePosition(const Plateau &position, unsigned currentDepth, int player);

private:
    unsigned maxDepth;
};

#endif // MINMAXAI_H
