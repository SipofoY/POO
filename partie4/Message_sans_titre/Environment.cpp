#include "Environment.hpp"
#include <vector>
#include "Application.hpp"
#include "ToricPosition.hpp"
#include "Animal.hpp"
#include "Anthill.hpp"
#include "Pheromone.hpp"
#include "Food.hpp"

void Environment::addAnimal(Animal* animal)
{
    if(animal!=nullptr) {
        faune.push_back(animal);
    }
}

void Environment:: addFood(Food* food)
{
    if(food!=nullptr) {
        nourritures.push_back(food);
    }
}

void Environment:: addAnthill(Anthill *anthill){
    if(anthill!=nullptr){
        maison.push_back(anthill);
    }
}

void Environment:: update(sf::Time dt)
{
    for(auto lesAnimaux: faune) {
        lesAnimaux->update(dt);
    }
    foodgenerator.update(dt);

    for(auto lesPher: pheromones) {
        lesPher->update(dt);
        if(lesPher->isNegligible()) {
            delete lesPher;
            lesPher=nullptr;
        }
    }

    for (auto lesmaisons : maison) {
        lesmaisons -> update(dt);
    }

}

void Environment:: drawOn(sf::RenderTarget& targetWindow)
{
    for(auto food_dessin:nourritures) {
        food_dessin->drawOn(targetWindow);
    }

     for(auto animal_dessin: faune) {
        if(!animal_dessin->isDead()) {
            animal_dessin->drawOn(targetWindow);
        }
    }

    for(auto pher_dessin: pheromones) {
        if(pher_ou_pas==true) {
            if(!pher_dessin->isNegligible()){
                pher_dessin->drawOn(targetWindow);
             }
        }
    }
    for (auto maison_dessin: maison) {
        maison_dessin->drawOn(targetWindow);
    }
}

void Environment:: reset()
{
    if (!faune.empty()) {
        for(auto element_faune: faune) {
            delete element_faune;
        }
        faune.clear();
    }
    if(!nourritures.empty()) {
        for(auto element_nourriture: nourritures) {
            delete element_nourriture;
        }
        nourritures.clear();
    }
    if(!pheromones.empty()) {
        for(auto element_pher: pheromones) {
            delete element_pher;
        }
        pheromones.clear();
    }

    if(!maison.empty()) {
        for(auto element_maison: maison) {
            delete element_maison;
        }
        maison.clear();
    }
}

void Environment:: addPheromone(Pheromone* pher)
{
    if(pher!= nullptr) {
        pheromones.push_back(pher);
    }
}

bool Environment:: togglePheromoneDisplay()
{
    if(pher_ou_pas) {
        return pher_ou_pas=false;
    }

    if(!pher_ou_pas) {
        return pher_ou_pas=true;
    }
}

Quantities Environment:: getPheromoneQuantitiesPerIntervalForAnt(
        const ToricPosition &position, Angle direction_rad, const Intervals &angles) {

    Intervals ensemble_angles({-180, -100, -55, -25, -10,  0, 10, 25,  55, 100, 180 });

    Quantities Q;

    for(auto les_pher: pheromones){
        if(toricDistance(les_pher->getPosition(), position)<getAppConfig().ant_smell_max_distance){
            Vec2d gamma= position.toricVector(les_pher->getPosition());
            Angle beta= (gamma.angle()-direction_rad)/DEG_TO_RAD;

            while(beta<0){
                beta+=360;
            }
            while(beta>=360){
                beta=beta-360;
            }

            Angle min=beta-ensemble_angles[0];
            for(unsigned int i(0); i< ensemble_angles.size(); ++i){
                Angle beta_prime=beta-ensemble_angles[i];
                if(beta_prime<min){
                    min=beta_prime;
                    Q[i]=les_pher->getQuantite();
                }

            }

        }
        return Q;
    }

}

Environment:: ~Environment(){
    getAppEnv().reset();
}

