
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "../Utility/Utility.hpp"
#include "Environment/Positionable.hpp"
#include "Random/RandomGenerator.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"

class Ant;
class Termite;

class Animal:public Positionable, public Drawable, public Updatable
{
protected:
    double pointvie;
    int esperancevie;
    Angle direction;
    sf::Time temps = sf::Time::Zero;
    void setDirection(Angle angle);
    bool Attack=false;



public:
    Angle getDirection() const;
    virtual int getSpeed() const;
    bool isDead() const;
    virtual void drawOn(sf::RenderTarget& target) const override;
    void move(sf::Time dt);
    virtual void update(sf::Time dt) override;
    RotationProbs computeRotationProbs();
    virtual bool isEnemy(Animal const* entity) const = 0;
    virtual bool isEnemyDispatch(Termite const* other) const = 0;
    virtual bool isEnemyDispatch(Ant const* other) const = 0;
    void setpointdevie(double point);
    double getPointVie() const;
    virtual std::string getTexture() const=0;

    Animal(Vec2d position, double pointvie, int esperancevie);
    Animal(int esperancevie, Vec2d position);
    Animal(double pointvie, Vec2d position);
    Animal(double pointvie1, int esperancevie1, Vec2d position1);
    Animal(double pointvie1, int esperancevie1);
    Animal(ToricPosition pos);
    Animal(ToricPosition pos, double pointvie1, int esperancevie1);

    virtual ~Animal(){}
};




#endif // ANIMAL_HPP
