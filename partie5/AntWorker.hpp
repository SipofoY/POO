#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#include "Ant.hpp"

class AntWorker: public Ant
{
public:
    AntWorker(Vec2d position1, Uid fourmil);
    AntWorker(ToricPosition pos, Uid fourmil);
    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;
    void demitour();
    void setmaxfood(double food);
    void resetfood();

private:
    double nourriture_transportee=0;

};

#endif // ANTWORKER_HPP
