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
    Ant(ToricPosition pos, Uid id);
    int getSpeed() const override;
    void drawnAnt(sf::RenderTarget& target, std::string  texture) const;// cette methode permet de dessiner l'Ant, on l'appelera dans la méthode drawn() de chaque fourmis
    void updatAnt(sf::Time dt);// cette methode permet de dessiner l'Ant, on l'appelera dans la méthode update() de chaque fourmis
    void spreadPheromones();
    void move(sf::Time dt);
    RotationProbs computeRotationProbs() const;
    Uid get_id() const;
    void affichage_probabilite(sf::RenderTarget& target) const;
    bool isEnemy(Animal const* animal) const override;
    bool isEnemyDispatch(Termite const*) const override;
    bool isEnemyDispatch(Ant const*) const override;
    virtual ~Ant(){}

private:
    Uid fourmilliere;
    ToricPosition lastSpreadPher;

};

#endif // ANT_HPP
