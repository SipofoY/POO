#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include"Animal.hpp"
#include"Food.hpp"
#include"FoodGenerator.hpp"


class Environment
{
public:
    void addAnimal(Animal* animal);
    void addFood(Food* food);
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& targetWindow) const; //void?
    void reset();

private:
    std::vector <Animal*> faune;
    std::vector <Food*> nourritures;
    FoodGenerator foodgenerator;
};


#endif // ENVIRONMENT_HPP
