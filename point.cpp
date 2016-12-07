#include "point.h"


Point::Point(int X ,int Y) : x(X), y(Y)
{

}

Point::Point() : x(0.0), y(0.0)
{

}

/*Point::Point(double X, double Y)
{
    x = X;
    y = Y;
}*/
/*
void Point::afficher( bool passer_a_la_ligne) const
{
    if(passer_a_la_ligne)
    {
        std::cout << "(" << x << ";" << y << ")" << std::endl;
    }
    else
    {
        std::cout << "(" << x << ";" << y << ")  ";
    }
}

std::string Point::text() const
{
    std::stringstream mon_flux (std::stringstream::in | std::stringstream::out);

    mon_flux << "(" << x << ";" << y << ")";

    return mon_flux.str();
}
*/
Point operator+(Point A, Point B)
{
    Point C;

    C.x = A.x + B.x;
    C.y = A.y + B.y;

    return C;
}

Point operator-(Point A, Point B)
{
    Point C;

    C.x = A.x - B.x;
    C.y = A.y - B.y;

    return C;
}

Point operator-(Point A)
{
    Point C;

    C.x = -A.x;
    C.y = -A.y;

    return C;
}

bool operator==(Point A, Point B)
{
    if(A.x == B.x && A.y == B.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float distance(Point A, Point B)
{
    return sqrt( pow( A.x - B.x , 2 ) + pow( A.y - B.y , 2 ));
}


