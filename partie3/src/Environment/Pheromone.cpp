#include "Pheromone.hpp"

#include"Utility/Utility.hpp"


Pheromone::Pheromone(ToricPosition pos, double Q)
{
    setPosition(pos);
    quantite=Q;
}

bool Pheromone::isNegligible()
{
    if(quantite<getAppConfig().pheromone_threshold) {
        return true;
    } else {
        return false;
    }
}

void Pheromone:: drawOn(sf::RenderTarget& target)
{
    auto const pheromoneSprite= buildCircle(getPosition().toVec2d(), 5, sf::Color::Green);
    target.draw(pheromoneSprite);

}

void Pheromone:: update(sf::Time dt)
{
    quantite=quantite-dt.asSeconds()*getAppConfig().pheromone_evaporation_rate;
}

double Pheromone:: getQuantite(){
    return quantite;
}

