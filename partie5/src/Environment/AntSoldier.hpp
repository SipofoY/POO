#ifndef ANTSOLDIER_HPP
#define ANTSOLDIER_HPP
#include "Ant.hpp"



class AntSoldier: public Ant
{
public:
    AntSoldier(Vec2d position1, Uid fourmil);
    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;
    std::string getTexture() const override;
    ~AntSoldier();
private:
    sf::Time compteur;

};


#endif // ANTSOLDIER_HPP
