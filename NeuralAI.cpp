#include "NeuralAI.h"

#include "NeuraleNetwork/SaveManager.h"
#include "config/config.h"
#include <vector>

NeuralAI::NeuralAI(int player, unsigned maxDepth):
    MinMaxAI(player, maxDepth)
{
    std::vector<unsigned int> layerSizes;
    for(unsigned int i = 0; i < NB_LAYERS; i++)
    {
      layerSizes.push_back(LAYER_SIZES[i]);
    }
    nn = new NeuralNetwork(layerSizes);
}

NeuralAI::NeuralAI(int player, unsigned maxDepth, const QString &pathToNN): NeuralAI(player,maxDepth)
{
    NeuralNetwork * loadedNeuralNetwork;
    loadedNeuralNetwork = SaveManager::LoadNetwork(pathToNN);
    if(loadedNeuralNetwork==nullptr)
    {
        std::cerr << "unabel to load Neurale Network at " << pathToNN.toStdString() << std::endl;
    }
    else
    {
        delete nn;
        nn = loadedNeuralNetwork;
    }
}

NeuralAI::NeuralAI(int player, unsigned maxDepth, NeuralNetwork &neuralNetwork): NeuralAI(player,maxDepth)
{
    delete nn;
    nn = new NeuralNetwork(neuralNetwork);
}

NeuralAI::~NeuralAI()
{
    if(nn != nullptr)
    {
        delete nn;
    }
}

bool NeuralAI::loadNeuralNetwork(const QString &pathToSavedNeuralNetwork)
{
    nn = SaveManager::LoadNetwork(pathToSavedNeuralNetwork);
    return nn != nullptr;
}

void NeuralAI::saveNeuralNetwork(const QString &pathToSavedNeuralNetwork) const
{
    SaveManager::SaveNetwork(*nn,pathToSavedNeuralNetwork);
}

double NeuralAI::getScorePosition(const Plateau &position)
{
    neuralNetworkInput.resize(BOARD_SIZE_X*BOARD_SIZE_Y);

    int caseValue;
    for(unsigned x=0 ; x<BOARD_SIZE_X ; x++)
    {
        for(unsigned y=0 ; y<BOARD_SIZE_Y ; y++)
        {
            caseValue = position.getCase(x,y);
            if(caseValue==playerNumber)
                neuralNetworkInput[x*8+y] = 1.0;
            else if(caseValue==0)
                neuralNetworkInput[x*8+y] = 0.0;
            else
                neuralNetworkInput[x*8+y] = -1.0;
        }
    }

    nn->run(neuralNetworkInput);//result is stored into input vector

    return neuralNetworkInput.at(0);
}


NeuralNetwork * NeuralAI::getNeuralNetwork()
{
    return nn;
}

void NeuralAI::setNeuralNetwork(NeuralNetwork neuraleNetwork)
{
    if(nn != nullptr)
    {
        delete nn;
    }
    nn = new NeuralNetwork(neuraleNetwork);
}















