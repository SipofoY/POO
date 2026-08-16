#ifndef TERMITE_HPP
#define TERMITE_HPP
#include "Animal.hpp"
#include "Ant.hpp"



class Termite: public Animal
{
public:
    Termite(ToricPosition pos);
    void move(sf::Time dt);
    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;
    bool isEnemy(Animal const* animal) const override;
    bool isEnemyDispatch(Termite const*) const override;
    bool isEnemyDispatch(Ant const*) const override;
    ~Termite(){}

private:
    double compteur;
};

#endif // TERMITE_HPP
