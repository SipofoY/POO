#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include "../Utility/Utility.hpp"
#include "FoodGenerator.hpp"
#include "Interface/Updatable.hpp"
#include <unordered_map>

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

    Food* getClosestFoodForAnt(ToricPosition const& position);
    Anthill* getAnthillForAnt(ToricPosition const& position, Uid anthillId);

    Quantities getPheromoneQuantitiesPerIntervalForAnt(
      const ToricPosition &position,
      Angle direction_rad,
      const Intervals &angles);

    Animal* getClosestEnemy(Animal* predator);
    std::unordered_map<std::string, double> fetchData(const std::string &);
    std::vector<std::string> getAnthillsIds() const;

    ~Environment();
    void decrease_AW();
    void increase_AW();
    void decrease_AS();
    void increase_AS();
    void decrease_T();
    void increase_T();


    double getTemperature();

protected:
    unsigned int antworker_compteur=0;
    unsigned int antsoldier_compteur=0;
    unsigned int termite_compteur=0;


private:
    std::vector <Animal*> faune;
    std::vector <Food*> nourritures;
    std::vector <Anthill*> maison;
    FoodGenerator foodgenerator;
    std::vector<Pheromone*> pheromones;
    bool pher_ou_pas;
    double Temperature=20.0;

    //Environment(const Environment&) = delete;
    //Environment& operator=(Environment) = delete;

};


#endif // ENVIRONMENT_HPP
