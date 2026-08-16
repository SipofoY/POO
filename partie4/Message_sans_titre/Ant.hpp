#ifndef ANT_HPP
#define ANT_HPP


#include "Utility/Utility.hpp"
#include"Application.hpp"
#include "Animal.hpp"


class Ant: public Animal
{
public:
    Ant(Vec2d position1, Uid fourmil);
    Ant(ToricPosition pos, Uid forurmil);
    Ant(Vec2d position1, Uid fourmil, double pointvie1, int esperancevie1);
    int getSpeed() const override;
    void drawnAnt(sf::RenderTarget& target, std::string  texture) const;// voir si on peut changer les argumetns à  l'interieur comme ceci
    //virtual void drawOn(sf::RenderTarget& target) const override;
    void move(sf::Time dt);
    void updateAnt(sf::Time dt);
    void spreadPheromones();
    RotationProbs computeRotationProbs();
    void affichage_probabilite(sf::RenderTarget target);
    ~Ant(){}
    bool isEnemy(Animal const* animal) const override;
    bool isEnemyDispatch(Termite const*) const override;
    bool isEnemyDispatch(Ant const*) const override;


private:
    Uid fourmilliere;
    ToricPosition lastSpreadPher;
};

#endif // ANT_HPP
