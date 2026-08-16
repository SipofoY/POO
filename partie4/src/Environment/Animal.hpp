#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "../Utility/Utility.hpp"
#include "Environment/Positionable.hpp"
#include "Random/RandomGenerator.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"

class Ant;
class Termite;
class Animal : public Positionable, public Drawable, public Updatable
{
protected:

    double pointvie;
    int esperancevie;
    Angle direction;
    sf::Time temps = sf::Time::Zero;
    void setDirection(Angle angle);
    bool Attack = false;
    bool Idle = true;
public:

    Angle getDirection() const;//cette methode nous retourne la direction  de l'animal
    virtual int getSpeed() const;//cette methode nous retourne la vitesse de l'animal
    bool isDead() const;//cette methode nous permet de savoir si l'animal est mort
    //void drawOn(sf::RenderTarget& target) const override;
    void move(sf::Time dt);// cette methode permet à l'animal de se déplacer
   // void update(sf::Time dt) override;
    RotationProbs computeRotationProbs();//cette methode permet d'avoir un angle de rotation lié à une probabilité
    virtual bool isEnemy(Animal const* entity) const = 0;// cette methode permet de voir si un animal est un enemie
    virtual bool isEnemyDispatch(Termite const* other) const = 0;//
    virtual bool isEnemyDispatch(Ant const* other) const = 0;//
    void setpointdevie(double point);//cette methode nous permet de changer les points de vies notamment pour les combats

    Animal(Vec2d position, double pointvie, int esperancevie);
    Animal(double pointvie1, int esperancevie1);
    Animal(double pointvie , int esperancevie, Vec2d position);
    Animal(int esperancevie, Vec2d position);
    Animal(double pointvie, Vec2d position);
    Animal(ToricPosition pos);
    Animal(ToricPosition pos, double pointvie1, int esperancevie1);
    Animal(double pointvie1, int esperancevie1, Vec2d position1, Angle direction);
    virtual~Animal(){}
};

#endif // ANIMAL_HPP
