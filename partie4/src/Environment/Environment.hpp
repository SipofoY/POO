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
class Termites;


class Environment
{
public:
    void addAnimal(Animal* animal);
    void addFood(Food* food);
    void addAnthill(Anthill * anthill);
    void update(sf::Time dt) ;
    void drawOn(sf::RenderTarget& targetWindow); //void?
    void reset();
    void addPheromone(Pheromone* pher);
    bool togglePheromoneDisplay();
    Quantities getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position, Angle direction_rad,const Intervals &angles);
    Food* getClosestFoodForAnt(ToricPosition const& position);
    Anthill* getAnthillForAnt(ToricPosition const& position, Uid anthillId);
    Animal* getClosestAnimal(ToricPosition const& position);
    ~Environment();
private:
    std::vector <Animal*> faune;
    std::vector <Food*> nourritures;
    std::vector <Anthill*> maison;
    FoodGenerator foodgenerator;
    std::vector<Pheromone*> pheromones;
    bool pher_ou_pas;
};


#endif // ENVIRONMENT_HPP
