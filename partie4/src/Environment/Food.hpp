#ifndef FOOD_HPP
#define FOOD_HPP
#pragma once
#include"Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include"Interface/Drawable.hpp"

class Food: public Positionable, public Drawable
{
public:
    Food(ToricPosition pos, Quantity quant);
    Quantity takeQuantity(Quantity quantite_donnee);
    void drawOn(sf::RenderTarget& target) const;
    virtual ~Food(){}
    double getQuantity();

private:
    Quantity quantite;

};


#endif // FOOD_HPP
