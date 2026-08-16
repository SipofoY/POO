#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include <vector>
#include "../Utility/Utility.hpp"
#include "FoodGenerator.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
/*#include "Animal.hpp"
#include "Food.hpp"
#include "Anthill.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"
*/

class Anthill;
class Animal;
class Food;
class AnSoldier;
class AntWorker;
class Pheromone;


class Environment: public Drawable, public Updatable
{
public:
    void addAnimal(Animal* animal);
    void addFood(Food* food);
    void addAnthill(Anthill * anthill);
    void update(sf::Time dt)  override;
    void drawOn(sf::RenderTarget& targetWindow) const override; //void?
    void reset();
    void addPheromone(Pheromone* pher);
    bool togglePheromoneDisplay();
    Quantities getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position, Angle direction_rad,const Intervals &angles);
    Food* getClosestFoodForAnt(ToricPosition const& position);
    Anthill* getAnthillForAnt(ToricPosition const& position, Uid anthillId);
private:
    std::vector <Animal*> faune;
    std::vector <Food*> nourritures;
    std::vector <Anthill*> maison;
    FoodGenerator foodgenerator;
    std::vector<Pheromone*> pheromones;
    bool pher_ou_pas;
    std :: vector <AntWorker*> workers;
};


#endif // ENVIRONMENT_HPP
