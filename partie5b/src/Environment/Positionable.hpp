/*
 * POOSV 2020-21
 * @author: 
 */

#pragma once

#include "../Utility/Vec2d.hpp"
#include "ToricPosition.hpp"
/*!
 * @brief Manage a position in a toric world
 *
 * 
 */
class Positionable
{
private:
    ToricPosition position;
public:
    /*! @brief constructeur de Positionable, un par defaut et l'autre prennant en paramètre un ToricPosition
*/
    Positionable();
    Positionable(ToricPosition p);

    /*! @brief cette méthode initialise la position avec un ToricPosition
     *  @param un Toricposition qui initialisera la position
*/
    ToricPosition setPosition(const ToricPosition& position);

    /*! @return elle retourne la position
*/
    ToricPosition getPosition() const;

    /*! @return cette méthode affiche les mêmes information que l'oppérateur <<
     *  @param cette méthode prend en paramtètre un std::ostream
*/
    std::ostream& display(std::ostream& out);

    /*! @brief Déstructeur de positionable
*/
    virtual ~Positionable(){}

};

    /*! @return c'est une surcharge externe de l'oppérateur <<
     *  @param elle prend en paramètre un std::ostream et un Positionable
*/
std::ostream& operator<<(std::ostream& out, Positionable const& P);


