#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP
#include<SFML/System.hpp>
#pragma once


class FoodGenerator
{
public:
    void update(sf::Time dt);
    FoodGenerator();


private:
    sf::Time compteur;
};

#endif // FOODGENERATOR_HPP
