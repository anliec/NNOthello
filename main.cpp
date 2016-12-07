#include "mainwindow.h"
#include "mygraphicsview.h"
#include <QApplication>
#include "Tournament.h"
#include "NeuralAI.h"
#include "BasicAI.h"
#include "RobionAI.h"

#include <ipp.h>

//#define TOURNAMENT

int main(int argc, char *argv[])
{
#ifndef TOURNAMENT
    QApplication a(argc, argv);
    MainWindow w;
    //MyGraphicsView w;
    w.show();
    return a.exec();
#else
    std::cout << "Tournament !" << std::endl;
    Tournament IAfight("BigRobionTournament2");
    std::shared_ptr<NeuralAI> winner;

    IAfight.runAIsTournament(2048,20);
    winner = IAfight.runAIsTournament(512,30);
//    IAfight.runChampionChip(1024);

//    for(int i=0 ; i<10 ; i++)
//    {
//        IAfight.runAIsTournament(512,1);
//        IAfight.runChampionChip(1024);
//    }

//    winner = IAfight.runChampionChip(1024);


    std::shared_ptr<RobionAI> basicAI = std::make_shared<RobionAI>(1,2);
    winner->setPlayerNumber(2);

    Jeux game(winner,basicAI);

    std::cout << "AI vs NN" << std::endl;
    std::cout << "AI: " << game.getPlateau().nbrJetonsJoueur(1);
    std::cout << " NN: " << game.getPlateau().nbrJetonsJoueur(2) << std::endl;

    winner->setPlayerNumber(1);
    basicAI->setPlayerNumber(2);

    Jeux game2(basicAI,winner);

    std::cout << "NN vs AI" << std::endl;
    std::cout << "AI: " << game2.getPlateau().nbrJetonsJoueur(2);
    std::cout << " NN: " << game2.getPlateau().nbrJetonsJoueur(1) << std::endl;

#endif

    return 0;
}
