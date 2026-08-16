#ifndef FOOD_HPP
#define FOOD_HPP
#pragma once
#include"Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>

class Food: public Positionable
{
public:
    Food(ToricPosition pos, Quantity quant);
    Quantity takeQuantity(Quantity quantite_donnee);
    void drawOn(sf::RenderTarget& target) const;

private:
    Quantity quantite;

};


#endif // FOOD_HPP
