#include "MinMaxAI.h"

MinMaxAI::MinMaxAI(unsigned playerNumber, unsigned explorationDepth):
    GameAI(playerNumber), maxDepth(explorationDepth)
{

}

Point MinMaxAI::play(const Plateau &position)
{
    Plateau tmpPosition;
    Point bestMove;
    double maxOutput = -INFINITY;
    double currentScore;
//    for(int x=0 ; x<BOARD_SIZE_X ; x++)
//    {
//        for(int y=0 ; y<BOARD_SIZE_Y ; y++)
//        {
//            if(position.peutEtreJouer(x,y,playerNumber))
//            {
    for(std::pair<unsigned,Point> value : position.getPlayablePosition())
    {
        if(position.peutEtreJouer(value.second,playerNumber))
        {
            tmpPosition = position;
            tmpPosition.jouerGeton(value.second,playerNumber);
            currentScore = getBestScorePosition(tmpPosition,1,Plateau::switchPlayer(playerNumber));
            if(maxOutput <= currentScore )
            {
                maxOutput = currentScore;
                bestMove = value.second;
                //            bestMove.x = x;
                //            bestMove.y = y;
            }
        }
    }
//            }
//        }
//    }
    return bestMove;
}

double MinMaxAI::getBestScorePosition(const Plateau &position, unsigned currentDepth, int player)
{
    if(currentDepth == maxDepth)
    {
        return getScorePosition(position);
    }
    Plateau tmpPosition;
    double bestOutput;
    if(currentDepth%2==1)
        bestOutput = INFINITY;
    else
        bestOutput = -INFINITY;

    double currentScore;
    for(std::pair<unsigned,Point> value : position.getPlayablePosition())
    {
        if(position.peutEtreJouer(value.second,player))
        {
            tmpPosition = position;
            tmpPosition.jouerGeton(value.second,player);
            currentScore = getBestScorePosition(tmpPosition,currentDepth+1,Plateau::switchPlayer(player));

            if(bestOutput >= currentScore && currentDepth%2==1)
                bestOutput = currentScore;
            else if(bestOutput <= currentScore && currentDepth%2==0)
                bestOutput = currentScore;
        }
    }
//    for(unsigned x=0 ; x<BOARD_SIZE_X ; x++)
//    {
//        for(unsigned y=0 ; y<BOARD_SIZE_Y ; y++)
//        {
//            if(position.peutEtreJouer(x,y,player))
//            {
//                tmpPosition = position;
//                tmpPosition.jouerGeton(x,y,player);
//                currentScore = getBestScorePosition(tmpPosition,currentDepth+1,Plateau::switchPlayer(playerNumber));

//                if(bestOutput >= currentScore && currentDepth%2==1)
//                    bestOutput = currentScore;
//                else if(bestOutput <= currentScore && currentDepth%2==0)
//                    bestOutput = currentScore;
//            }
//        }
//    }
    return bestOutput;
}
