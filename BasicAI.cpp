#include "BasicAI.h"

BasicAI::BasicAI(unsigned playerNum, unsigned AIlevel):
    GameAI(playerNum),
    niveauIA(AIlevel)
{

}

double BasicAI::getScorePosition(const Plateau &position)
{
    return 0.0;
}

Point BasicAI::play(const Plateau &position)
{
    int Xmax = position.getXmax(), Ymax= position.getYmax();

    int bestX=-1, bestY=-1;
    double bestscore=COEF_CASENONJOUABLE+1; //on retourne (-1;-1) si aucune case n'est jouable, équivalant à passer le tour...

    for(int x=0 ; x<Xmax ; x++)
    {
        for(int y=0 ; y<Ymax ; y++)
        {
            double coef = coefIAcase(x,y,position);

            if(coef >= bestscore)
            {
                bestX = x;
                bestY = y;
                bestscore = coef;
            }
        }
    }

    return Point(bestX,bestY);
}

double BasicAI::coefIAcase(int x, int y, const Plateau &position)
{
    return coefIAcase(x,y,position,playerNumber);
}

double BasicAI::coefIAcase(int x, int y, const Plateau &position, int playerNum)
{
    if(position.peutEtreJouer(x,y,playerNum))
    {
        double coef=0.0;
        if(niveauIA<2){ // si l'IA est en facile ou moins
            coef = double(position.simulationCoup(Point(x,y), playerNum));
        }
        else{ // sinon
            coef = simulationCoupCoef(x,y,position,playerNum);
        }

        if(niveauIA>0) //si l'IA n'est pas en débutant
            coef += calculCoefCasePosition(x,y,position);
        if(niveauIA>1){ //si l'IA est en Normale ou plus
            coef -= calculCoefCasePositionTourSuivant(x,y,position,Plateau::switchPlayer(playerNum));
        }
        return coef;
    }
    else
    {
        return COEF_CASENONJOUABLE;
    }
}

double BasicAI::calculCoefCasePosition(int x, int y, const Plateau &position)
{
    int Xmax = position.getXmax()-1, Ymax= position.getYmax()-1;
    double coef = 0.0;

    //gestion des coef négatif pour les ligne proche des bords
    if(x==1 && (y<Ymax-1 && y>1)){
        for(int i=y-1;i<=y+1;i++){
            if(position.getCase(Point(0,i))>0){
                coef -= COEF_LIGNEMOINS /3.0;
            }
        }
    }
    if(x==Xmax-1 && (y<Ymax-1 && y>1)){
        for(int i=y-1;i<=y+1;i++){
            if(position.getCase(Point(Xmax,i))>0){
                coef -= COEF_LIGNEMOINS /3.0;
            }
        }
    }
    if(y==1 && (x<Xmax-1 && x>1)){
        for(int i=x-1;i<=x+1;i++){
            if(position.getCase(Point(i,x))>0){
                coef -= COEF_LIGNEMOINS /3.0;
            }
        }
    }
    if(y==Ymax-1 && (x<Xmax-1 && x>1)){
        for(int i=x-1;i<=x+1;i++){
            if(position.getCase(Point(i,Ymax))>0){
                coef -= COEF_LIGNEMOINS /3.0;
            }
        }
    }
    //gestion des coef positif pour les bords
    if((x==0 || x==Xmax) || (y==0 || y==Ymax)){
        coef += COEF_LIGNEPLUS;
    }
    //gestion des coef négatif proche des angles
    if( (x<=1 && y<=1 && position.getCase(Point(0,0))==0 ) || (x<=1 && y>=Ymax-1 && position.getCase(Point(0,Ymax))==0) || (x>=Xmax-1 && y<=1 && position.getCase(Point(Xmax,0))==0 ) || (x>=Xmax-1 && y>=Ymax-1 && position.getCase(Point(Xmax,Ymax))==0 )){
        coef -= COEF_COINMOINS;
    }
    //gestion des coef possitif pour les angles
    if( (x==0 && y==0) || (x==0 && y==Ymax) || (x==Xmax && y==0) || (x==Xmax && y==Ymax) ){
        coef += COEF_COINPLUS - 2*COEF_LIGNEPLUS;
    }

    return coef;
}

double BasicAI::calculCoefCasePositionTourSuivant(int x, int y, const Plateau &position, int joueur)
{
    Plateau simulation(position);
    simulation.jouerGeton(x,y,joueur);

    //set AI to facile because of infinite loop
    int oldAIlevel = niveauIA;
    niveauIA = IA_FACILE;

    int otherPlayer = Plateau::switchPlayer(joueur);

    double meilleurcoef = -COEF_COINMOINS;
    for(int a=0 ; a<simulation.getXmax() ; a++){
        for(int b=0 ; b<simulation.getYmax() ; b++){
            double coefCase = coefIAcase(a,b,simulation,otherPlayer);
            if(coefCase>meilleurcoef){
                meilleurcoef = coefCase;
            }
        }
    }
    //get AI level back to the old seting
    niveauIA = oldAIlevel;
    return meilleurcoef;
}

double BasicAI::simulationCoupCoef(int x, int y, const Plateau &position, int joueur)
{
    Point pointJouer(x,y);
    double nbrPionRetournerCoef(position.simulationCoup(pointJouer,joueur));

    if(x==0 || x==position.getXmax()-1){
        nbrPionRetournerCoef += COEF_LIGNEPLUSRETOURNER*double(position.examinerLigneDepuisNbrCase(pointJouer, 0, 1, joueur)+position.examinerLigneDepuisNbrCase(pointJouer, 0, -1, joueur));
        bool ligneSur = true;
        for(int i=0;i<position.getYmax();i++){
            if(position.getCase(x,i)==joueur || position.getCase(x,i)==0)
                ligneSur = false;
        }
        if(ligneSur){
            nbrPionRetournerCoef += COEF_LIGNEPLUSSEUL;
        }
    }
    else if(y==0 || y==position.getXmax()-1){
        nbrPionRetournerCoef += COEF_LIGNEPLUSRETOURNER*double(position.examinerLigneDepuisNbrCase(pointJouer, 1, 0, joueur)+position.examinerLigneDepuisNbrCase(pointJouer, -1, 0, joueur));
        bool ligneSur = true;
        for(int i=0;i<position.getXmax();i++){
            if(position.getCase(i,y)==joueur || position.getCase(i,y)==0)
                ligneSur = false;
        }
        if(ligneSur){
            nbrPionRetournerCoef += COEF_LIGNEPLUSSEUL;
        }
    }

    return nbrPionRetournerCoef;
}

double BasicAI::simulationCoupCoef(Point pointJouer, const Plateau &position, int joueur)
{
    return simulationCoupCoef(pointJouer.x,pointJouer.y,position,joueur);
}










int BasicAI::getNiveauIA() const
{
    return niveauIA;
}

void BasicAI::setNiveauIA(int nivIA)
{
    if(nivIA>=0 && nivIA<=2){
        niveauIA = nivIA;
    }
}
