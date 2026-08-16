#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#include "Ant.hpp"

class AntWorker: public Ant
{
private:
    double maxfood;
public:
    AntWorker(Vec2d position1, Uid fourmil);
    AntWorker(ToricPosition position1, Uid fourmil);
    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;
    void demitour();
    void setmaxfood(double food);
    void resetfood();
};

#endif // ANTWORKER_HPP
