#include "jeux.h"

//Jeux::Jeux(Plateau table, int numJoueurIA, int typeIA, int niveauDeIA) : QObject(), plateau(table),\
//    joueurIA(numJoueurIA), niveauIA(niveauDeIA), neuralAI(joueurIA,2)
//{
//    nbrTour=0;
//    IAapueJouer = true;
//    defaultAI = typeIA;
//    partieTerminee = false;

//    QObject::connect(this,SIGNAL(partieFini()),this,SLOT(finDePartie()));
//}

//Jeux::Jeux(int numJoueurIA) : Jeux(Plateau(),numJoueurIA)
//{

//}

Jeux::Jeux(std::shared_ptr<GameAI> AIplayer2, std::shared_ptr<GameAI> AIplayer1):
    Jeux(Plateau(),AIplayer2,AIplayer1)
{
}

Jeux::Jeux(const Plateau &table, std::shared_ptr<GameAI> AIplayer2, std::shared_ptr<GameAI> AIplayer1):
    joueur1(AIplayer1),
    joueur2(AIplayer2),
    plateau(table)
{
    partieTerminee = false;
    nbrTour=0;
    QObject::connect(this,SIGNAL(partieFini()),this,SLOT(finDePartie()));

    currentPlayer = 1;
    //if player is an AI player then let it play
    if(joueur1 != nullptr)
    {
        jouerIA();
    }
}

Jeux::~Jeux()
{

}

bool Jeux::jouer(Point P)
{
    return jouer(P.x,P.y);
}

bool Jeux::jouer(int x, int y)
{
    if(plateau.peutEtreJouer(x,y,currentPlayer))
    {
        plateau.jouerGeton(x,y,currentPlayer);
        //current player played go to next player
        currentPlayer = Plateau::switchPlayer(currentPlayer);
        //if current player is now AI let it play
        if(isAIplayer(currentPlayer))
        {
            jouerIA(); //recursive call (if both player are AI)
        }
        return true;
    }
    else if(!plateau.peutJouer(currentPlayer))
    {
        currentPlayer = Plateau::switchPlayer(currentPlayer);
        if(!plateau.peutJouer(currentPlayer))
        {
            //if both player can't play game end.
            emit partieFini();
            return false;
        }
        else
        {
            //if current player is now AI let it play
            if(isAIplayer(currentPlayer))
            {
                jouerIA(); //recursive call (if both player are AI)
            }
            return false;
        }
    }
    else
    {
        return false;
    }
}

//bool Jeux::jouer(int x, int y, bool IA)
//{
//    if(plateau.peutEtreJouer(x,y,1))
//    {
//        // le joueur humain joue:
//        plateau.jouerGeton(x,y,1);
//        // l'IA joue:
//        if(IA){
//            Point coup = coupIA();
//            if(plateau.peutEtreJouer(coup,joueurIA)){
//                poserJeton(coup,joueurIA);
//                //plateau.jouerGeton(coup,2);
//                IAapueJouer = true;
//            }
//            else{
//                IAapueJouer = false;
//                //std::cerr << "AI try to play at (" << coup.x << ";" << coup.y << ") but it's not possible." << std::endl;
//            }
//        }

//        nbrTour ++;

//        if(plateau.estPlein()){
//            emit partieFini();
//        }
//        else if(plateau.nbrJetonsJoueur(1) == 0 || plateau.nbrJetonsJoueur(2) == 0){
//            emit partieFini();
//        }
//    }
//    else if(!plateau.peutJouer(1)){
//        if(IA){
//            if(IAapueJouer == false){
//                emit partieFini();// si l'IA n'a pas pue jouer avant, la partie est finie le joueur avec le plus de jetons gagne //le joueur 1 est vainceur
//            }
//            else{
//                Point coup = coupIA();
//                if(plateau.peutEtreJouer(coup,2)){
//                    //plateau.jouerGeton(coup,2);
//                    poserJeton(coup,2);
//                }
//                else{
//                    emit partieFini();// si l'IA ne peut pas jouer non plus, la partie est finie la joueur avec le plus de jetons gagne ///elle est vainceur
//                }
//            }
//        }
//    }
//    else
//        return false;

//    return true;
//}

//void Jeux::boucleIA()
//{
//    Point coup;
//    while (!partieTerminee) {
//        coup = coupIA(NN_AI,1);
//        if(!jouer(coup,true))
//        {
//            std::cerr << "infinite loop !" << std::endl;
//            break;
//        }
//    }
//}

void Jeux::jouerIA()
{
    //plateau.jouerGeton(coupIA(),2);
    //plateau.jouerGeton(neuralAI.play(plateau),joueurIA);
    Point coup;
    coup = getAIplayer(currentPlayer)->play(plateau);
    jouer(coup); //recursive call (if both player are AI)
}


Plateau Jeux::getPlateau() const
{
    return plateau;
}

//double Jeux::coefIAcase(int x, int y, int joueur) const
//{
//    if(plateau.peutEtreJouer(x,y,joueur))
//    {
//        double coef=0.0;
//        if(niveauIA<2){ // si l'IA est en facile ou moins
//            coef = double(plateau.simulationCoup(Point(x,y), joueur));
//        }
//        else{ // sinon
//            coef = simulationCoupCoef(x,y,joueur);
//        }

//        if(niveauIA>0) //si l'IA n'est pas en débutant
//            coef += calculCoefCasePosition(x,y);
//        if(niveauIA>1){ //si l'IA est en Normale ou plus
//            coef -= calculCoefCasePositionTourSuivant(x,y,1);
//        }
//        return coef;
//    }
//    else
//    {
//        return COEF_CASENONJOUABLE;
//    }
//}

//double Jeux::calculCoefCasePosition(int x, int y) const
//{
//    int Xmax = plateau.getXmax()-1, Ymax= plateau.getYmax()-1;
//    double coef = 0.0;

//    //gestion des coef négatif pour les ligne proche des bords
//    if(x==1 && (y<Ymax-1 && y>1)){
//        for(int i=y-1;i<=y+1;i++){
//            if(plateau.getCase(Point(0,i))>0){
//                coef -= COEF_LIGNEMOINS /3.0;
//            }
//        }
//    }
//    if(x==Xmax-1 && (y<Ymax-1 && y>1)){
//        for(int i=y-1;i<=y+1;i++){
//            if(plateau.getCase(Point(Xmax,i))>0){
//                coef -= COEF_LIGNEMOINS /3.0;
//            }
//        }
//    }
//    if(y==1 && (x<Xmax-1 && x>1)){
//        for(int i=x-1;i<=x+1;i++){
//            if(plateau.getCase(Point(i,x))>0){
//                coef -= COEF_LIGNEMOINS /3.0;
//            }
//        }
//    }
//    if(y==Ymax-1 && (x<Xmax-1 && x>1)){
//        for(int i=x-1;i<=x+1;i++){
//            if(plateau.getCase(Point(i,Ymax))>0){
//                coef -= COEF_LIGNEMOINS /3.0;
//            }
//        }
//    }
//    //gestion des coef positif pour les bords
//    if((x==0 || x==Xmax) || (y==0 || y==Ymax)){
//        coef += COEF_LIGNEPLUS;
//    }
//    //gestion des coef négatif proche des angles
//    if( (x<=1 && y<=1 && plateau.getCase(Point(0,0))==0 ) || (x<=1 && y>=Ymax-1 && plateau.getCase(Point(0,Ymax))==0) || (x>=Xmax-1 && y<=1 && plateau.getCase(Point(Xmax,0))==0 ) || (x>=Xmax-1 && y>=Ymax-1 && plateau.getCase(Point(Xmax,Ymax))==0 )){
//        coef -= COEF_COINMOINS;
//    }
//    //gestion des coef possitif pour les angles
//    if( (x==0 && y==0) || (x==0 && y==Ymax) || (x==Xmax && y==0) || (x==Xmax && y==Ymax) ){
//        coef += COEF_COINPLUS - 2*COEF_LIGNEPLUS;
//    }

//    return coef;
//}

//double Jeux::calculCoefCasePositionTourSuivant(int x, int y, int joueur) const
//{
//    Jeux simulation;
//    simulation.setPlateau(plateau);
//    simulation.setNiveauIA(IA_FACILE);
//    simulation.jouerUnJetons(x,y,joueur);
//    double meilleurcoef = -COEF_COINMOINS;
//    for(int a=0 ; a<simulation.getPlateau().getXmax() ; a++){
//        for(int b=0 ; b<simulation.getPlateau().getYmax() ; b++){
//            double coefCase = simulation.coefIAcase(a,b,joueur);
//            if(coefCase>meilleurcoef){
//                meilleurcoef = coefCase;
//            }
//        }
//    }
//    return meilleurcoef;
//}

//double Jeux::simulationCoupCoef(int x, int y, int joueur) const
//{
//    Point pointJouer(x,y);
//    double nbrPionRetournerCoef(plateau.simulationCoup(pointJouer,joueur));

//    if(x==0 || x==plateau.getXmax()-1){
//        nbrPionRetournerCoef += COEF_LIGNEPLUSRETOURNER*double(plateau.examinerLigneDepuisNbrCase(pointJouer, 0, 1, joueur)+plateau.examinerLigneDepuisNbrCase(pointJouer, 0, -1, joueur));
//        bool ligneSur = true;
//        for(int i=0;i<plateau.getYmax();i++){
//            if(plateau.getCase(x,i)==joueur || plateau.getCase(x,i)==0)
//                ligneSur = false;
//        }
//        if(ligneSur){
//            nbrPionRetournerCoef += COEF_LIGNEPLUSSEUL;
//        }
//    }
//    else if(y==0 || y==plateau.getXmax()-1){
//        nbrPionRetournerCoef += COEF_LIGNEPLUSRETOURNER*double(plateau.examinerLigneDepuisNbrCase(pointJouer, 1, 0, joueur)+plateau.examinerLigneDepuisNbrCase(pointJouer, -1, 0, joueur));
//        bool ligneSur = true;
//        for(int i=0;i<plateau.getXmax();i++){
//            if(plateau.getCase(i,y)==joueur || plateau.getCase(i,y)==0)
//                ligneSur = false;
//        }
//        if(ligneSur){
//            nbrPionRetournerCoef += COEF_LIGNEPLUSSEUL;
//        }
//    }

//    return nbrPionRetournerCoef;
//}

//double Jeux::simulationCoupCoef(Point pointJouer, int joueur) const
//{
//    return simulationCoupCoef(pointJouer.x,pointJouer.y, joueur);
//}

//Point Jeux::coupIA()
//{
//    return coupIA(defaultAI);
//}

//Point Jeux::coupIA(int IAtype, int joueur)
//{
//    if(IAtype==BASIC_AI)
//    {
//        int Xmax = plateau.getXmax(), Ymax= plateau.getYmax();

//        int bestX=-1, bestY=-1;
//        double bestscore=COEF_CASENONJOUABLE+1; //on retourne (-1;-1) si aucune case n'est jouable, équivalant à passer le tour...

//        for(int x=0 ; x<Xmax ; x++)
//        {
//            for(int y=0 ; y<Ymax ; y++)
//            {
//                double coef = coefIAcase(x,y);

//                if(coef >= bestscore)
//                {
//                    bestX = x;
//                    bestY = y;
//                    bestscore = coefIAcase(x,y);
//                }
//            }
//        }

//        return Point(bestX,bestY);
//    }
//    else if(IAtype==NN_AI)
//    {
//        return neuralAI.play(plateau,joueur);
//    }
//    return Point();
//}

//int Jeux::getNiveauIA() const
//{
//    return niveauIA;
//}

//void Jeux::setNiveauIA(int nivIA)
//{
//    if(nivIA>=0 && nivIA<=2){
//        niveauIA = nivIA;
//    }
//}

void Jeux::setPlateau(Plateau table){
    plateau = table;
}

void Jeux::jouerUnJetons(int x, int y, int joueur){
    plateau.jouerGeton(x,y,joueur);
}

void Jeux::sauvgarderCoup(PointJoueur pointJ){
    sav.push_back(pointJ);
}

void Jeux::sauvgarderCoup(Point point, int joueur){
    sauvgarderCoup(PointJoueur(point, joueur));
}

void Jeux::sauvgarderCoup(int x, int y, int joueur){
    sauvgarderCoup(Point(x,y), joueur);
}

void Jeux::poserJeton(Point point, int joueur){
    plateau.jouerGeton(point,joueur);
    sauvgarderCoup(point, joueur);
}

void Jeux::poserJeton(int x, int y, int joueur){
    poserJeton(Point(x,y), joueur);
}

//NeuralNetwork Jeux::getNeuralNetwork()
//{
//    return *(neuralAI.getNeuralNetwork());
//}

void Jeux::finDePartie()
{
    partieTerminee=true;
}

bool Jeux::estTerminee() const
{
    return partieTerminee;
}

//void Jeux::setNeuralNetwork(NeuralNetwork nn)
//{
//    neuralAI.setNeuralNetwork(nn);
//}

bool Jeux::isAIplayer(int playerNumber) const
{
    switch (playerNumber) {
    case 1:
        return joueur1!=nullptr;
    case 2:
        return joueur2!=nullptr;
    default:
        return false;
    }
}

std::shared_ptr<GameAI> Jeux::getAIplayer(int playerNumber) const
{
    switch (playerNumber) {
    case 1:
        return joueur1;
    case 2:
        return joueur2;
    default:
        return std::shared_ptr<GameAI>(); //nullptr
    }
}
