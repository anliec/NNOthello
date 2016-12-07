#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "NeuraleNetwork/NeuralNetwork.h"
#include <memory>
#include <QString>
#include <QtXml>

static const QString savePath("../save/");

/*
 * The Save Manager class is designed to manage all save and load operations.
 * In particular it can write and read xml files and their object counterparts
 */
class SaveManager
{
public:
    // constructor
//    SaveManager();

    //Network operations
    static int SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName="temp");
    static int SaveNetwork(const NeuralNetwork& nn, QXmlStreamWriter & writer);
    static NeuralNetwork *LoadNetwork(QString neuralNetworkName="temp");
    static NeuralNetwork *LoadNetwork(QXmlStreamReader& reader);

private:
    //Parsers
    static int parseNeuralNetwork(QXmlStreamReader& reader, std::vector<std::vector<std::vector<double> > > &neuronWeights);
    static void parseWeights(QString weights, std::vector<double> &weightsArray);
};

#endif // SAVEMANAGER_H
