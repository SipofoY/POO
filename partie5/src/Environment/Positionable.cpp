/*
 *
 * POOSV 2020-21
 * @author:
 */
#include <iostream>
#include <ostream>
#include "Positionable.hpp"
ToricPosition Positionable :: setPosition(const ToricPosition& pos){

    position = pos;

    return position;
}
std::ostream& operator<<(std::ostream& out, Positionable const& P){

    out << P.getPosition();
    return out;
}
std :: ostream& Positionable :: display(std :: ostream& out){

    return out << position;
}
ToricPosition Positionable :: getPosition() const{
     return position;
 }
Positionable:: Positionable()
    : position(0.0,0.0){}
Positionable:: Positionable(ToricPosition p)
    : position(p){}
