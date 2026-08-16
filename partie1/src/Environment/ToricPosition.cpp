/*
 * POOSV 2020-21
 * @author:
 */

#include "ToricPosition.hpp"
#include <cmath>
#include "Application.hpp"
#include <array>
void ToricPosition::clamp()
{
    double calcul1;
    double calcul2;
    calcul1 = coordonees.x() + fmod(coordonees.x(), dimensions.x());
    if (calcul1<0){
        calcul1+=dimensions.x();
    }
    calcul2=coordonees.y() + fmod(coordonees.y(), dimensions.y());
    if(calcul2<0){
        calcul2+=dimensions.y();
    }
    Vec2d fin_calcul(calcul1, calcul2);
    coordonees= fin_calcul;
}


ToricPosition::ToricPosition(Vec2d test, Vec2d testdim)
{
    ToricPosition TE(test, testdim);
    TE.clamp();
    coordonees = test;
    dimensions = testdim;
}
ToricPosition::ToricPosition(double a, double b)
{
    Vec2d coordtest(a,b);
    double dimension(getAppConfig().simulation_size);
    Vec2d dimtest(dimension, dimension);
    ToricPosition TA(coordtest, dimtest);
    TA.clamp();
    coordonees= coordtest;
    dimensions = dimtest;

}
ToricPosition::ToricPosition()
    : coordonees(0.0,0.0)
{}

ToricPosition::ToricPosition(ToricPosition const& recopie)
{
    coordonees = recopie.coordonees;
    dimensions = recopie.dimensions;
}
double ToricPosition::operator[](int index) const
{switch (index) {
    case 0:
        return coordonees.x();

    case 1:
        return coordonees.y();
        break;}
}
Vec2d ToricPosition::toricVector(ToricPosition const& that)const{
    std::array <double,9> tj; // Nous savons qu'il y a 9 possibilité donc nous pouvons resoudre le problème avec un tableau array.
    std::array <Vec2d, 9> tab;
    double min;
    Vec2d min1;
    Vec2d plusw(dimensions.x(),0), plush(0, dimensions.y()), toutdim(dimensions.x(), dimensions.y()), toutdim2(dimensions.x(),  -dimensions.y());// comment acceder a dimensions

    tab[0]= that.coordonees;
    tab[1]= that.coordonees + plusw;
    tab[2]= that.coordonees + plush;
    tab[3]= that.coordonees - plusw;
    tab[4]= that.coordonees - plush;
    tab[5]= that.coordonees + toutdim;
    tab[6]= that.coordonees - toutdim;
    tab[7]= that.coordonees + toutdim2;
    tab[8]= that.coordonees - toutdim2;

    for (int i(0);i<9;++i){
        tj[i] = distance(this->coordonees, tab[i]); // comment marche this et pourquoi coordones ne marche pas
    }
    min = tj[0];
    for (int i(0); i< 9; ++i){
       if (tj[i] < min){
           min = tj[i];
           min1 = tab[i];
       }

    }
    return min1;
}


Vec2d const& ToricPosition:: toVec2d(ToricPosition obj){
    return obj.coordonees;
}

double ToricPosition:: x() const{
    return coordonees.x();
}

double ToricPosition:: y() const{
    return coordonees.y();
}


ToricPosition& ToricPosition:: operator+=(ToricPosition const& toric){
    double cal1(coordonees.x());
    double cal2(coordonees.y());
    cal1+=toric.coordonees.x();
    cal2+=toric.coordonees.y();
    Vec2d tot(cal1, cal2);
    coordonees = tot;
    ToricPosition all(coordonees, dimensions);
    all.clamp();
    return all;
}

const ToricPosition ToricPosition:: operator+(ToricPosition const& toric) //il fait quoi?
{
    ToricPosition od = *this;
    return od +=toric;
}

std::ostream& operator<<(std::ostream& out, ToricPosition const& P){

    out << P.x() << P.y(); // demander si cette methode est bien faites
    return out;
}
double toricDistance(ToricPosition const& from, ToricPosition const& to){
        Vec2d distance1;
        distance1 = from.toricVector(to);
        return distance1.length();

}

