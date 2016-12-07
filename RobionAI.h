#ifndef ROBIONAI_H
#define ROBIONAI_H

#include "MinMaxAI.h"

class RobionAI : public MinMaxAI
{
public:
    RobionAI(int player, unsigned maxDepth);

protected:
    virtual double getScorePosition(const Plateau &position);
};

#endif // ROBIONAI_H
