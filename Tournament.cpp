#include "Tournament.h"
#include "NeuraleNetwork/SaveManager.h"
#include <QDir>
#include <QFile>

#include "BasicAI.h"
#include "NeuralAI.h"
#include "RobionAI.h"

Tournament::Tournament(QString name):
    tournamentName(name)
{
    stageNumber = -1;
}


void Tournament::saveAI(const NeuralNetwork &nn, unsigned roundNumber, unsigned AInumber) const
{
    QString directoryName(tournamentName);
    directoryName.append("/stage_").append(QString::number(stageNumber))\
            .append("/round_").append(QString::number(roundNumber));
    QDir saveDirectory(directoryName);

    if(!saveDirectory.exists())
    {
        saveDirectory.mkpath(".");
    }

    QString saveFilePath;
    saveFilePath.append(directoryName).append('/').append(QString::number(AInumber)).append(".xml");

    SaveManager::SaveNetwork(nn,saveFilePath);
}

void Tournament::appendResult(unsigned roundNumber, unsigned AInumber, unsigned NNscore, unsigned AIscore)
{
    QString directoryName(tournamentName);
    directoryName.append("/stage_").append(QString::number(stageNumber))\
            .append("/round_").append(QString::number(roundNumber));
    QDir saveDirectory(directoryName);

    if(!saveDirectory.exists())
    {
        saveDirectory.mkpath(".");
    }

    QString fileName;
    fileName.append(directoryName).append("/results.txt");
    QFile resultFile( fileName );
    if(resultFile.open(QIODevice::Append))
    {
        QTextStream stream( &resultFile);
        stream << "NN n" << AInumber << " basic AI: " << AIscore << " | NN AI: " << NNscore;
        if(NNscore > AIscore)
        {
            stream << " NN win !";
            if(NNscore+AIscore < BOARD_SIZE_X*BOARD_SIZE_Y)
            {
                stream << " by blocking AI (" << BOARD_SIZE_X*BOARD_SIZE_Y-NNscore-AIscore << " turns before end)";
            }
        }
//        else
//            stream << " NN lose...\n";
        stream << "\n";
        resultFile.close();
    }
}

void Tournament::appendResult(unsigned roundNumber, unsigned AInumber1, unsigned AInumber2, unsigned scoreP1, unsigned scoreP2)
{
    QString directoryName(tournamentName);
    directoryName.append("/stage_").append(QString::number(stageNumber))\
            .append("/round_").append(QString::number(roundNumber));
    QDir saveDirectory(directoryName);

    if(!saveDirectory.exists())
    {
        saveDirectory.mkpath(".");
    }

    QString fileName;
    fileName.append(directoryName).append("/results.txt");
    QFile resultFile( fileName );
    if(resultFile.open(QIODevice::Append))
    {
        QTextStream stream( &resultFile);
        stream << "NN " << AInumber1 << "vs" << AInumber2 << " || player1: " << scoreP1 << " | player2: " << scoreP2 <<"\n";
        resultFile.close();
    }
}


std::shared_ptr<NeuralAI> Tournament::runAIsTournament(unsigned numberOfNeuralAi, unsigned numberOfRound)
{
    stageNumber++;

    for(unsigned roundNum=0 ; roundNum<numberOfRound ;roundNum++)
    {
        if(roundNum!=0)
        {
            seedAI = bestAI;
        }
        bestAIscore = -1;

        for(unsigned AInum=0 ; AInum<numberOfNeuralAi ; AInum++)
        {
            std::shared_ptr<RobionAI> AIplayer1 = std::make_shared<RobionAI>(1,2);
            std::shared_ptr<NeuralAI> AIplayer2 = std::make_shared<NeuralAI>(2);

            if(seedAI != nullptr)
            {
                NeuralNetwork nn(*(seedAI->getNeuralNetwork()));
                nn.randomiseWeight();
                AIplayer2->setNeuralNetwork(nn);
            }

            saveAI(*(AIplayer2->getNeuralNetwork()),roundNum,AInum);

            //construct and play as both player are AI
            Jeux game(AIplayer2,AIplayer1);

            int scoreNN1 = game.getPlateau().nbrJetonsJoueur(2);
            int scoreAI1 = game.getPlateau().nbrJetonsJoueur(1);
            appendResult(roundNum,AInum,scoreNN1,scoreAI1);

            ///inverse player and play it again !

            AIplayer2->setPlayerNumber(1);
            AIplayer1->setPlayerNumber(2);
            Jeux game2(AIplayer1,AIplayer2);

            int scoreNN2 = game2.getPlateau().nbrJetonsJoueur(1);
            int scoreAI2 = game2.getPlateau().nbrJetonsJoueur(2);
            int scoreNN = scoreNN2 + scoreNN1;
            int scoreAI = scoreAI1 + scoreAI2;
            appendResult(roundNum,AInum,scoreNN2,scoreAI2);

            //if NN win boths games then add a bonnus score
            if(scoreNN1 > scoreAI1 && scoreNN1 > scoreNN2)
            {
                scoreNN += 2*BOARD_SIZE_X*BOARD_SIZE_Y;
                //if NN win by blocking AI then add an other bonnus score
                if(scoreAI+scoreNN<2*BOARD_SIZE_X*BOARD_SIZE_Y)
                {
                    int diffToMaxTurn = 2*BOARD_SIZE_X*BOARD_SIZE_Y - (scoreNN+scoreAI);
                    scoreNN += std::pow(diffToMaxTurn,2);
                }
            }
            if(bestAIscore < scoreNN)
            {
                bestAI = AIplayer2;
                bestAIscore = scoreNN;
            }
        }
        //do convergence stuff between round
    }
    if(bestAI!=nullptr)
        saveAI(*(bestAI->getNeuralNetwork()),numberOfRound,0);
    else
        std::cerr << "Tournament run but no winner were found" << std::endl;
    seedAI=bestAI;
    return bestAI;
}

std::shared_ptr<NeuralAI> Tournament::runChampionChip(unsigned numberOfAi)
{
    if(seedAI==nullptr)
    {
        std::vector<unsigned int> layerSizes;
        for(unsigned int i = 0; i < NB_LAYERS; i++)
        {
            layerSizes.push_back(LAYER_SIZES[i]);
        }
        return runChampionChip(numberOfAi,NeuralNetwork(layerSizes));
    }
    else //if a seed is avaible use it
    {
        return runChampionChip(numberOfAi,*(seedAI->getNeuralNetwork()));
    }
}

std::shared_ptr<NeuralAI> Tournament::runChampionChip(unsigned numberOfAi, NeuralNetwork sourceNetwork)
{
    stageNumber++;
    //check that numberOfAi is a power of 2 ?

    std::vector<std::shared_ptr<NeuralAI>> lastWinner;
    std::vector<std::shared_ptr<NeuralAI>> currentWinner;

    //initialisation
    for(unsigned i=0; i<numberOfAi ; i++)
    {
        NeuralNetwork nn(sourceNetwork);
        nn.randomiseWeight();
        std::shared_ptr<NeuralAI> nAI;
        nAI = std::make_shared<NeuralAI>(1,2,nn);
        lastWinner.push_back(nAI);
    }

    int roundNumber = 0;
    while (lastWinner.size() > 1)
    {
        int AInumber=0;
        while (lastWinner.size() > 1)
        {
            std::shared_ptr<NeuralAI> player1;
            std::shared_ptr<NeuralAI> player2;

            player1 = lastWinner.back();
            lastWinner.pop_back();
            player1->setPlayerNumber(1);
            saveAI(*(player1->getNeuralNetwork()),roundNumber,AInumber++);
            player2 = lastWinner.back();
            lastWinner.pop_back();
            player2->setPlayerNumber(2);
            saveAI(*(player2->getNeuralNetwork()),roundNumber,AInumber++);

            Jeux game(player2,player1);

            int scoreP1 = game.getPlateau().nbrJetonsJoueur(1);
            int scoreP2 = game.getPlateau().nbrJetonsJoueur(2);
            appendResult(roundNumber,AInumber-2,AInumber-1,scoreP1,scoreP2);
            if(scoreP1 > scoreP2)
            {
                currentWinner.push_back(player1);
            }
            else
            {
                currentWinner.push_back(player2);
            }
        }
        lastWinner = currentWinner;
        currentWinner.clear();
        roundNumber++;
    }
    bestAI = lastWinner.front();
    seedAI = lastWinner.front();
    return bestAI;
}












