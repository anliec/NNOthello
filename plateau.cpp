#include "plateau.h"

Plateau::Plateau()
{
    for(int x=0; x<BOARD_SIZE_X ; x++)
    {
        for(int y=0;y<BOARD_SIZE_Y;y++)
        {
            table[x][y]=0;
        }
    }
    playablePosition.reserve(64); // reserve the max number of token to be sure

    retourner( Point( (BOARD_SIZE_X-1)/2    , (BOARD_SIZE_Y-1)/2     ) , 1 );
    retourner( Point( (BOARD_SIZE_X-1)/2    , (BOARD_SIZE_Y-1)/2 + 1 ) , 2 );
    retourner( Point( (BOARD_SIZE_X-1)/2 + 1, (BOARD_SIZE_Y-1)/2 + 1 ) , 1 );
    retourner( Point( (BOARD_SIZE_X-1)/2 + 1, (BOARD_SIZE_Y-1)/2     ) , 2 );

}
/*
void Plateau::afficher()
{
    for(int y=0 ; y<BOARD_SIZE_Y ; y++)
    {
        for(int x=0 ; x<BOARD_SIZE_X ; x++)
        {
            std::cout << table[x][y] << " ";
        }
        std::cout << std::endl;
    }
}
*/
int Plateau::getCase(int x, int y) const
{
    if(x>=0 && x<BOARD_SIZE_X && y>=0 && y <BOARD_SIZE_Y) /// si l'on ne sort pas du tableau
    {
        return table[x][y];
    }
    else
    {
        return -1; //code erreur
    }
}

int Plateau::getCase(Point coordonee) const
{
    return getCase(coordonee.x,coordonee.y);
}

bool Plateau::ajouterGeton(int x, int y, int valeur, bool coordonneeHumaine)
{
    if(coordonneeHumaine)
    {
        x--;
        y--;
    }

    if(peutEtreJouer(x,y))
    {
        retourner(x,y,valeur);
        //table[x][y] = valeur;
        return true;
    }
    else
    {
        return false;
    }
}

bool Plateau::ajouterGeton(Point coordonee, int valeur, bool coordoneeHumaine)
{
    return ajouterGeton(coordonee.x, coordonee.y, valeur, coordoneeHumaine);
}

bool Plateau::peutEtreJouer(int x, int y) const
{
    return playablePosition.find(y*BOARD_SIZE_X+x) != playablePosition.end();

//    if(x>=0 && x<BOARD_SIZE_X && y>=0 && y <BOARD_SIZE_Y) /// si l'on ne sort pas du tableau
//    {
//        if(table[x][y] != 0) /// si il y a déjà un geton sur la case on ne peut pas jouer
//        {
//            return false;
//        }

//        for(int i=-1 ; i<=1 ; i++)
//        {
//            for(int n=-1 ; n<=1 ; n++)
//            {
//                if(x+i>=0 && x+i<BOARD_SIZE_X && y+n>=0 && y+n <BOARD_SIZE_Y) /// si l'on ne sort pas du tableau
//                {
//                    if(i!=0 || n!=0) /// on ne prend pas en compte la case du centre
//                    {
//                        if(table[x+i][y+n] != 0) /// si il y a quelque chose autour on indique que l'on peut jouer
//                        {
//                            return true;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return false;
}

bool Plateau::peutEtreJouer(int x, int y, int joueur) const
{
    if(peutEtreJouer(x,y))
    {
        //a optimiser...
        //if(simulationCoup(Point(x,y),joueur) > 1){ //si il y a au moins un pion retourner autre que celui jouer
        if(isATokenReversed(Point(x,y),joueur)){
            return true;
        }
        else{
            return false;
        }
        /* a parrement les règle ce n'est pas comme ça...
        else if(nbrJetonsJoueur(joueur)==0){ //si le joueur n'a pas de jetons il peut jouer quand même
            return true;
        }
        else{
            for(int a=0 ; a<BOARD_SIZE_X ; a++){
                for(int b=0 ; b<BOARD_SIZE_Y ; b++){
                    if(peutEtreJouer(a,b)){
                        if(simulationCoup(Point(a,b),joueur) > 1){
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        */
    }
    else{
        return false;
    }
}

bool Plateau::peutEtreJouer(Point coordonee) const
{
    return peutEtreJouer(coordonee.x,coordonee.y);
}

bool Plateau::peutEtreJouer(Point coordonee, int joueur) const
{
    return peutEtreJouer(coordonee.x,coordonee.y,joueur);
}

bool Plateau::peutJouer(int joueur) const
{
    for(std::pair<unsigned,Point> value : playablePosition)
    {
        if(peutEtreJouer(value.second, joueur))
        {
            return true;
        }
    }
    return false;
}

bool Plateau::estPlein() const
{
    return playablePosition.size() == 0; //id there are no playable position board is full (or empty)
//    for(int x=0; x<BOARD_SIZE_X ; x++)
//    {
//        for(int y=0;y<BOARD_SIZE_Y;y++)
//        {
//            if(table[x][y] == 0)
//                return false;
//        }
//    }
//    return true;
}

void Plateau::retourner(int x, int y, int versValeur, bool newToken)
{
    if(x>=0 && x<BOARD_SIZE_X && y>=0 && y <BOARD_SIZE_Y) /// si l'on ne sort pas du tableau
    {
        table[x][y]=versValeur;

        if(versValeur!=0 && newToken) //if we are not seting the case as empty and if we are not reversing already played token
        {
            unsigned key = y*BOARD_SIZE_X+x;
            playablePosition.erase(key);
            //look for the empty case around the current case and add them in playable position
            //if they are currently empty
            for(int dx=-1 ; dx<=1 ; dx++)
            {
                for(int dy=-1 ; dy<=1 ; dy++)
                {
                    if(getCase(x+dx,y+dy)==0) // handle also the case where dx=dy=0 as (x,y) is set to non zero value
                    {
                        playablePosition[(y+dy)*BOARD_SIZE_X+x+dx] = Point(x+dx,y+dy); //insert
                    }
                }
            }
        }
    }
}

void Plateau::retourner(Point coordonee, int versValeur, bool newToken)
{
    retourner(coordonee.x,coordonee.y,versValeur,newToken);
}

int Plateau::getXmax() const
{
    return BOARD_SIZE_X;
}
int Plateau::getYmax() const
{
    return BOARD_SIZE_Y;
}

int Plateau::simulationCoup(Point pointJouer, int joueur) const
{
    int nbrPionRetourner = 1;

    for(int dx=-1 ; dx<=1 ; dx++)
    {
        for(int dy=-1 ; dy<=1 ; dy++)
        {
            nbrPionRetourner += examinerLigneDepuisNbrCase(pointJouer, dx, dy, joueur);
        }
    }
    return nbrPionRetourner;
}

bool Plateau::isATokenReversed(Point playedPosition, int playerNumber) const
{
    for(int dx=-1 ; dx<=1 ; dx++)
    {
        for(int dy=-1 ; dy<=1 ; dy++)
        {
            if(examinerLigneDepuisNbrCase(playedPosition, dx, dy, playerNumber) > 0)
            {
                return true;
            }
        }
    }
    return false;
}

std::unordered_map<unsigned, Point> Plateau::getPlayablePosition() const
{
    return playablePosition;
}

Point Plateau::examinerLigneDepuis(Point depart, int dx, int dy, int joueur) const
{
    Point i=depart;
    int valCase;

    do
    {
        i.x += dx;
        i.y += dy;
        valCase = getCase(i);
    }while(valCase!=joueur && valCase!=0 && valCase!=-1);

    if(valCase == joueur)
    {
        return i;
    }
    else
    {
        return depart;
    }
}

int Plateau::examinerLigneDepuisNbrCase(Point depart, int dx, int dy, int joueur) const
{
    Point i=depart;
    int valCase=0;
    int n=0;

    do
    {
        i.x += dx;
        i.y += dy;
        n++;
        valCase = getCase(i);
    }while(valCase!=joueur && valCase!=0 && valCase!=-1);

    if(valCase == joueur)
    {
        return n-1;
    }
    else
    {
        return 0;
    }
}

void Plateau::retournerLigne(Point depart, int dx, int dy, int nbrIteration)
{
    int joueur=getCase(depart);

    for(int i=1 ; i<=nbrIteration ; i++)
    {
        retourner(depart+Point(i*dx,i*dy),joueur,false);
    }
}

void Plateau::jouerGeton(Point depart, int joueur)
{
    retourner(depart,joueur);

    for(int dx=-1 ; dx<=1 ; dx++)
    {
        for(int dy=-1 ; dy<=1 ; dy++)
        {
            int iteration;
            iteration = examinerLigneDepuisNbrCase(depart, dx, dy, joueur);
            retournerLigne(depart,dx,dy,iteration);
        }
    }

}

void Plateau::jouerGeton(int x, int y, int joueur)
{
    jouerGeton(Point(x,y),joueur);
}

int Plateau::nbrJetonsJoueur(int numJoueur) const
{
    int nbr=0;
    for(int x=0 ; x<BOARD_SIZE_X ; x++){
        for(int y=0 ; y<BOARD_SIZE_Y ; y++){
            if(getCase(x,y) == numJoueur){
                nbr++;
            }
        }
    }
    return nbr;
}

int Plateau::switchPlayer(int currentPlayer)
{
    return 3 - currentPlayer; // if currentPlayer=2 return 1 else if currentPlayer=1 return 2
}





