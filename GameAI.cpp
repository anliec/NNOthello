#include "GameAI.h"

GameAI::GameAI(unsigned playerNum): playerNumber(playerNum)
{

}

int GameAI::getPlayerNumber() const
{
    return playerNumber;
}

void GameAI::setPlayerNumber(int playerNum)
{
    if(playerNum==1 || playerNum==2)
        playerNumber = playerNum;
}
