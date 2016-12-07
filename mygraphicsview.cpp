#include "mygraphicsview.h"
#include "BasicAI.h"
#include "NeuralAI.h"
#include "RobionAI.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);

    ///réglage graphique:
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ///mises en place du jeux:

    brushJ1 = QBrush(Qt::green);
    brushJ2 = QBrush(Qt::red);
    //brushJ0 = QBrush(Qt::transparent);

    //penJ0 = QPen(Qt::transparent);
    penJ1 = QPen();
    penJ2 = QPen();

//    afficherCoefIA = false;

    this->setScene(scene);

    nouvellePartie();

    //setModeJeuxIA(0); // IA en mode de jeux normale

    ///configuration de la boite de dialogue de fin de partie:
    messageBoxFinPArtie = new QMessageBox;


    QObject::connect(jeux, SIGNAL(partieFini()), this, SLOT(finDePartie()));
    QObject::connect(jeux, SIGNAL(partieFini(int)), this, SLOT(finDePartie(int)));
}

void MyGraphicsView::mousePressEvent(QMouseEvent * e)
  {
      QPointF mousePoint = mapToScene(e->pos());

      Point p;
      p.x = int(mousePoint.x()/a);
      p.y = int(mousePoint.y()/b);

      jeux->jouer(p);

      actualiserAffichage();

  }

void MyGraphicsView::resizeEvent(QResizeEvent *event)
{    
    actualiserAffichage();
    fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

//void MyGraphicsView::setAfficherCoefIA(bool afficher)
//{
//    afficherCoefIA = afficher;
//    actualiserAffichage();
//}

void MyGraphicsView::actualiserTailleCase()
{  
    a = size().width() / jeux->getPlateau().getXmax() -1;
    b = size().height() / jeux->getPlateau().getYmax() -1;
    if(a<b){
        b=a;
    }
    else{
        a=b;
    }
}

void MyGraphicsView::actualiserAffichage()
{
    actualiserTailleCase();

    scene->setSceneRect(0,0,jeux->getPlateau().getXmax()*a,jeux->getPlateau().getYmax()*b);

    //on efface tout:
    foreach(QGraphicsItem *item,   scene->items())
    {
          scene->removeItem(item);
    }

    //et on recrée le plateau:
    for(int x=0 ; x<=jeux->getPlateau().getXmax() ; x++)
    {
        for(int y=0 ; y<=jeux->getPlateau().getYmax() ; y++)
        {
            switch(jeux->getPlateau().getCase(Point(x,y)))
            {
            case 0:
                scene->addEllipse(x*a,y*b,a,b,QPen(Qt::gray),QBrush(Qt::white));
                break;
            case 1:
                scene->addEllipse(x*a,y*b,a,b,QPen(),brushJ1);
                break;
            case 2:
                scene->addEllipse(x*a,y*b,a,b,QPen(),brushJ2);
                break;
            }
        }
        emit aChanger();
    }

//    if(afficherCoefIA) // pour debug
//    {
//        for(int x=0 ; x<jeux->getPlateau().getXmax() ; x++)
//        {
//            for(int y=0 ; y<jeux->getPlateau().getYmax() ; y++)
//            {
//                QGraphicsTextItem *coef;
//                QFont font;
//                font.setPointSize(8);
//                coef = scene->addText(QString::number(jeux->coefIAcase(x,y)));
//                coef->setPos(x*a+a/3,y*b+b/2-10);
//                coef->setFont(font);
//            }
//        }
//    }

}

//void MyGraphicsView::faireJouerIA()
//{
//    jeux->jouerIA();
//    actualiserAffichage();
//}

//void MyGraphicsView::setModeJeuxIA(int mode)
//{
//    modeJeuxIA = mode;
//}

int MyGraphicsView::nbrJetons(int numJoueur)
{
    return jeux->getPlateau().nbrJetonsJoueur(numJoueur);
}

//int MyGraphicsView::heightForWidth( int w ) { return w; }

void MyGraphicsView::finDePartie()
{
    int vainceur = 0;
    if(jeux->getPlateau().nbrJetonsJoueur(2) > jeux->getPlateau().nbrJetonsJoueur(1))
        vainceur = 2;
    else if(jeux->getPlateau().nbrJetonsJoueur(2) == jeux->getPlateau().nbrJetonsJoueur(1))
        vainceur = 0;
    else
        vainceur = 1;

    finDePartie(vainceur);
}

void MyGraphicsView::finDePartie(int vainceur)
{
    actualiserAffichage();

    QString textMB;

    switch(vainceur){
    case 1:
        textMB = "Vous avez gagner, bravo ! il faudra une IA bien meilleur pour pouvoir vous batre.";
        break;
    case 2:
        textMB = "Vous avez perdue, l'IA à été plus forte que vous cette fois ci";
        break;
    case 0:
        textMB = "Egalité !";
        break;
    }

    messageBoxFinPArtie->setText(textMB +"\nVoullez vous refaire une partie ?");
    messageBoxFinPArtie->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBoxFinPArtie->setDefaultButton(QMessageBox::Yes);

    int ret = messageBoxFinPArtie->exec();

    if(ret == QMessageBox::Yes){
        nouvellePartie();
    }
    else
        emit finDuJeux();
}

//void MyGraphicsView::setNiveauIA(int nivIA)
//{
//    jeux->setNiveauIA(nivIA);
//}

void MyGraphicsView::nouvellePartie()
{
//    std::shared_ptr<BasicAI> player2AI = std::make_shared<BasicAI>(2);
    std::shared_ptr<NeuralAI> player2AI = std::make_shared<NeuralAI>(1,4,"AIs/bigRobionTournament2.xml");
//    std::shared_ptr<RobionAI> player2AI = std::make_shared<RobionAI>(2,4);
    jeux = new Jeux(std::shared_ptr<GameAI>(),player2AI);

    actualiserAffichage();
}
