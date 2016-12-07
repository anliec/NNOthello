#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

/*#include <iostream>
#include <sstream>*/
#include <cmath>


class Point
{
    public:

    Point(int X , int Y = 0 );
    Point();
    //Point(double X , double Y = 0.0);

    /*void afficher(bool passer_a_la_ligne = true) const;
    std::string text() const;*/

    int x;
    int y;

};

Point operator+(Point A, Point B);
Point operator-(Point A, Point B);
Point operator-(Point A);
bool operator==(Point A, Point B);

float distance(Point A, Point B);


#endif // POINT_H_INCLUDED
