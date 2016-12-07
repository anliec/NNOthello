#include "RobionAI.h"

RobionAI::RobionAI(int player, unsigned maxDepth):
    MinMaxAI(player, maxDepth)
{

}

double RobionAI::getScorePosition(const Plateau &position)
{
    int score = 0;
    int currentScore;
    for(unsigned x=0 ; x<BOARD_SIZE_X ; x++)
    {
        for(unsigned y=0 ; y<BOARD_SIZE_Y ; y++)
        {
            if(position.getCase(x,y) != 0)
            {
                if( (x==0 || x==BOARD_SIZE_X-1) && (y==0 || y==BOARD_SIZE_Y-1) )
                {
                    currentScore = 80;
                }
                else if( x==0 || x==BOARD_SIZE_X-1 || y==0 || y==BOARD_SIZE_Y-1 )
                {
                    currentScore = 10;
                }
                else if( (x==1 || x==BOARD_SIZE_X-2) && (y==1 || y==BOARD_SIZE_Y-2) )
                {
                    currentScore = -30;
                }
                else if( x==1 || x==BOARD_SIZE_X-2 || y==1 || y==BOARD_SIZE_Y-2 )
                {
                    currentScore = -5;
                }
                else
                {
                    currentScore = 1;
                }
                if(position.getCase(x,y) == getPlayerNumber())
                {
                    score += currentScore;
                }
                else
                {
                    score -= currentScore;
                }
            }
        }
    }
    return static_cast<double>(score);
}
