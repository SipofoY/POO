#include "Environment.hpp"
#include <vector>
#include"ToricPosition.hpp"
#include "Application.hpp"
#include "Animal.hpp"
#include "Food.hpp"
#include "Anthill.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"
#include"Pheromone.hpp"




void Environment::addAnimal(Animal* animal){
   if(animal!=nullptr){
   faune.push_back(animal);
   }
}

void Environment:: addFood(Food* food){
    if(food!=nullptr){
    nourritures.push_back(food);
    }
}


void Environment :: addAnthill(Anthill * anthill){
    if (anthill!= nullptr){
    maison.push_back(anthill);
    }
}

void Environment:: addPheromone(Pheromone* pher)
{
    if(pher!= nullptr) {
        pheromones.push_back(pher);
    }
}

void Environment:: update(sf::Time dt){
    Food* te;
    Anthill* ta;
   for(auto lesAnimaux: faune){
       lesAnimaux->update(dt);
   }            //faire évoluer les animaux de la faune ici
   foodgenerator.update(dt);

   for (auto lesmaisons : maison){
       lesmaisons -> update(dt);
   }
   for(auto lesPher: pheromones) {
       if(lesPher->isNegligible()) {
           delete lesPher;

       }
       lesPher->update(dt);
   for (size_t i(0); i< workers.size(); ++i){
       te = getClosestFoodForAnt( workers[i]->getPosition());
       if (toricDistance(te->getPosition(), workers[i]->getPosition()) <= getAppConfig().ant_max_perception_distance){
       te->takeQuantity(getAppConfig().ant_max_food);
       workers[i]->setmaxfood(getAppConfig().ant_max_food);

       }
       ta = getAnthillForAnt(workers[i]->getPosition(), workers[i]->get_id());
       if (toricDistance(ta->getPosition(), workers[i]->getPosition()) <= getAppConfig().ant_max_perception_distance){
          ta -> setstock(getAppConfig().ant_max_food);
          workers[i] -> resetfood();
       }else {
           workers[i]->demitour();
       }
   }

}

}
void Environment:: drawOn(sf::RenderTarget& targetWindow) const{
    for(auto food_dessin:nourritures){
        food_dessin->drawOn(targetWindow);
    }
    for(auto animal_dessin: faune){
        if(!animal_dessin->isDead()){
            animal_dessin->drawOn(targetWindow);
        }
    }
        for(auto pher_dessin: pheromones) {
            if(pher_ou_pas) {
                pher_dessin->drawOn(targetWindow);
            }
        }

    for (auto maison_dessin: maison){
        maison_dessin->drawOn(targetWindow);
    }
}
    //a faire quand les animaux et les sources de nourriture deviendront plus concrets


void Environment:: reset(){
    if (!faune.empty()){
        for(auto element_faune: faune){
            delete element_faune;
        }
        faune.clear();
    }
    if(!nourritures.empty()){
        for(auto element_nourriture: nourritures){
            delete element_nourriture;
        }
        nourritures.clear();
    }
    if(!pheromones.empty()) {
        for(auto element_pher: pheromones) {
            delete element_pher;
        }
    }
    pheromones.clear();
    if(!maison.empty()) {
        for(auto element_maison: maison) {
            delete element_maison;
        }
        maison.clear();
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
    }
    return Q;
}
Food* Environment::getClosestFoodForAnt(ToricPosition const& position){

    Food* min= nourritures[1];
    for(size_t i(0); i< nourritures.size(); ++i){
        if(toricDistance(nourritures[i]->getPosition(), position)<toricDistance(min->getPosition(), position) and toricDistance(nourritures[i]->getPosition(), position) <= getAppConfig().ant_max_perception_distance){
            min = nourritures[i];
        }
    }
    return min;
}
Anthill* Environment ::getAnthillForAnt(ToricPosition const& position, Uid anthillId){
    Anthill* min;
    for(size_t i(0); i< maison.size(); ++i){
        if(toricDistance(maison[i]->getPosition(), position)<= getAppConfig().ant_max_perception_distance and maison[i]->get_id() == anthillId){
            min = maison[i];
        }
        else {
            return nullptr;
        }

    }
    return min;


}
