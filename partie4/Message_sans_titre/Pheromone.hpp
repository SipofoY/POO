#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP
#include "Positionable.hpp"
#include"Application.hpp"


class Pheromone: public Positionable
{
public:
    Pheromone(ToricPosition pos, double Q);
    bool isNegligible();
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& target) const;
    double getQuantite() const;

private:
    double quantite;
    sf::Color color=sf::Color::Green;
};

#endif // PHEROMONE_HPP
