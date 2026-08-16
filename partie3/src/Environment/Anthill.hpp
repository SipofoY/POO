#ifndef ANTHILL_HPP
#define ANTHILL_HPP
#include "Animal.hpp"
#include "Utility/Utility.hpp"
#include <vector>
#include "Food.hpp"

class Anthill : public Positionable, public Drawable, public Updatable
{
public:
    Anthill(ToricPosition position);
    void drawOn(sf::RenderTarget& target) const override;
    Prob probworker();
    void update(sf::Time dt) override;
    Uid get_id();
    void setstock(double food);
private:
    double stock;
    Uid identifiant;
    sf::Time temps = sf::Time::Zero;


};

#endif // ANTHILL_HPP
