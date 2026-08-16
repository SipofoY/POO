/*
 * POOSV 2020-21
 * @author:
 */

#pragma once
#include "../Utility/Vec2d.hpp"

/*!
 * @brief Handle toric coordinate, distance and other
 * basic math operation in a toric world
 *
 * @note Gets the dimensions of the world from getAppConfig()
 */

class ToricPosition
{
private:
    Vec2d coordonees;
    Vec2d dimensions;

    void clamp();


public:
    ToricPosition(Vec2d test, Vec2d testdim);
    ToricPosition(double a, double b);
    ToricPosition();
    ToricPosition(ToricPosition const& recopie);
    double operator[](int index) const;
    Vec2d toricVector(ToricPosition const& that)const;

    void swap(ToricPosition& toric1, ToricPosition& toric2); //il faut mettre les parametres??

    ToricPosition& operator=(ToricPosition const& toric)=default;
    Vec2d const& toVec2d(ToricPosition obj);
    double x() const;
    double y() const;
    ToricPosition& operator+=(ToricPosition const&);
    const ToricPosition operator+(ToricPosition const& toric);

};

std::ostream& operator<<(std::ostream& out, ToricPosition const& P);


// FONCTION A COMPLETER
double toricDistance(ToricPosition const& from, ToricPosition const& to);
