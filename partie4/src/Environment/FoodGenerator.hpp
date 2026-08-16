#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP
#include<SFML/System.hpp>
#pragma once
#include"Interface/Updatable.hpp"

class FoodGenerator: public Updatable
{
public:
    void update(sf::Time dt);
    FoodGenerator();


private:
    sf::Time compteur;
};

#endif // FOODGENERATOR_HPP
