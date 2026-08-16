#ifndef ANT_HPP
#define ANT_HPP
#include "Animal.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"

class Ant: public Animal
{
public:
    Ant(Vec2d position1, Uid fourmil);
    Ant(Vec2d position1, Uid fourmil ,double pointvie, int esperancevie);
    int getSpeed() const override;
    void drawnAnt(sf::RenderTarget& target, std::string  texture) const;// voir si on peut changer les argumetns à  l'interieur comme ceci
    void updatAnt(sf::Time dt);
    void spreadPheromones();
    void move(sf::Time dt);
    RotationProbs computeRotationProbs();
    void affichage_probabilite(sf::RenderTarget target);
    Uid get_id();
    ~Ant(){}
private:
    Uid fourmilliere;
    ToricPosition lastSpreadPher;

};

#endif // ANT_HPP
