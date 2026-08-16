#pragma once
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <SFML/Graphics.hpp>
#include <Utility/Types.hpp>
#include "Environment/Positionable.hpp"
#include "Random/RandomGenerator.hpp"


class Animal : public Positionable
{
private:

    double pointvie;
    int esperancevie;
    Angle direction;
    sf::Time temps = sf::Time::Zero;
public:

    Angle getDirection();
    int getSpeed();
    void setDirection(Angle angle);
    bool isDead();
    void drawOn(sf::RenderTarget& target);
    void move(sf::Time dt);
    void update(sf::Time dt);
    RotationProbs computeRotationProbs();

    Animal(double pointvie , int esperancevie, Vec2d position);
    Animal(int esperancevie, Vec2d position);
    Animal(double pointvie, Vec2d position);
};

#endif // ANIMAL_HPP
