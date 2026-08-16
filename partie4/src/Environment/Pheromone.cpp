#include "Pheromone.hpp"

#include"Utility/Utility.hpp"


Pheromone::Pheromone(ToricPosition pos, double Q)
{
    setPosition(pos);
    quantite=Q;
    color.a/=5;
}

bool Pheromone::isNegligible()
{
    if(quantite<getAppConfig().pheromone_threshold) {
        return true;
    } else {
        return false;
    }
}

void Pheromone:: drawOn(sf::RenderTarget& target) const
{
    ToricPosition pos=this->getPosition();
    auto const pheromoneSprite= buildCircle(pos.toVec2d(), 5, color);
    target.draw(pheromoneSprite);
}

void Pheromone:: update(sf::Time dt)
{
    quantite=quantite-dt.asSeconds()*getAppConfig().pheromone_evaporation_rate;
}

double Pheromone:: getQuantite() const{
    return quantite;
}

