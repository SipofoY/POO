#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "../Utility/Utility.hpp"
#include "Environment/Positionable.hpp"
#include "Random/RandomGenerator.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"


class Animal : public Positionable, public Drawable, public Updatable
{
protected:

    double pointvie;
    int esperancevie;
    Angle direction;
    sf::Time temps = sf::Time::Zero;
    void setDirection(Angle angle);
public:

    Angle getDirection() const;
    virtual int getSpeed() const;
    bool isDead();
    //void drawOn(sf::RenderTarget& target) const override;
    void move(sf::Time dt);
   // void update(sf::Time dt) override;
    RotationProbs computeRotationProbs();
    Animal(double pointvie1, int esperancevie1);
    Animal(double pointvie , int esperancevie, Vec2d position);
    Animal(int esperancevie, Vec2d position);
    Animal(double pointvie, Vec2d position);
};

#endif // ANIMAL_HPP
