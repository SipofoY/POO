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
    Positionable();
    Positionable(ToricPosition p);
    ToricPosition setPosition(const ToricPosition& position);
    ToricPosition getPosition() const;
    std::ostream& display(std::ostream& out);

};

std::ostream& operator<<(std::ostream& out, Positionable const& P);


