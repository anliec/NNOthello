#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "jeux.h"
#include <QString>
#include "NeuraleNetwork/NeuralNetwork.h"
#include "NeuralAI.h"

class Tournament
{
public:
    Tournament(QString name);

    std::shared_ptr<NeuralAI> runAIsTournament(unsigned numberOfNeuralAi, unsigned numberOfRound = 1);
    std::shared_ptr<NeuralAI> runChampionChip(unsigned numberOfAi, NeuralNetwork sourceNetwork);
    std::shared_ptr<NeuralAI> runChampionChip(unsigned numberOfAi);

private:
    void saveAI(const NeuralNetwork &nn, unsigned roundNumber, unsigned AInumber) const;
    void appendResult(unsigned roundNumber, unsigned AInumber, unsigned NNscore, unsigned AIscore);
    void appendResult(unsigned roundNumber, unsigned AInumber1, unsigned AInumber2, unsigned scoreP1, unsigned scoreP2);

private:
    QString tournamentName;
    std::shared_ptr<NeuralAI> seedAI;
    std::shared_ptr<NeuralAI> bestAI;
    int bestAIscore;
    int stageNumber;
};

#endif // TOURNAMENT_H
