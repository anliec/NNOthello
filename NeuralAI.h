#ifndef NEURALAI_H
#define NEURALAI_H

#include <QString>
#include "NeuraleNetwork/NeuralNetwork.h"
#include "plateau.h"
#include "point.h"

#include "MinMaxAI.h"

class NeuralAI : public MinMaxAI
{
public:
    NeuralAI(int player, unsigned maxDepth = 2);
    NeuralAI(int player, unsigned maxDepth, const QString &pathToNN);
    NeuralAI(int player, unsigned maxDepth, NeuralNetwork &nn);
    virtual ~NeuralAI();

    bool loadNeuralNetwork(const QString &pathToSavedNeuralNetwork);
    void saveNeuralNetwork(const QString &pathToSavedNeuralNetwork) const;

    NeuralNetwork * getNeuralNetwork();
    void setNeuralNetwork(NeuralNetwork nn);

protected:
    virtual double getScorePosition(const Plateau &position);

private:
    NeuralNetwork * nn;
    std::vector<double> neuralNetworkInput;
};

#endif // NEURALAI_H
