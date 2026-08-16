#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include "../Utility/Utility.hpp"
#include "FoodGenerator.hpp"
#include "Interface/Updatable.hpp"

class Anthill;
class Animal;
class Pheromone;
class Food;


class Environment
{
public:
    void addAnimal(Animal* animal);
    void addFood(Food* food);
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& targetWindow);
    void reset();
    void addPheromone(Pheromone* pher);
    bool togglePheromoneDisplay();
    void addAnthill(Anthill* anthill);

    Quantities getPheromoneQuantitiesPerIntervalForAnt(
      const ToricPosition &position,
      Angle direction_rad,
      const Intervals &angles);
    ~Environment();



private:
    std::vector <Animal*> faune;
    std::vector <Food*> nourritures;
    std::vector <Anthill*> maison;
    FoodGenerator foodgenerator;
    std::vector<Pheromone*> pheromones;
    bool pher_ou_pas;

    //Environment(const Environment&) = delete;
    //Environment& operator=(Environment) = delete;

};


#endif // ENVIRONMENT_HPP
