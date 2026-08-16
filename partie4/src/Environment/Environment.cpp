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
#include "Termite.hpp"




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

   //comment faire pour selectionner seulement les fourmis ouvrière


   for(auto lesAnimaux: faune){

       lesAnimaux->update(dt);
   }            //faire évoluer les animaux de la faune ici



   foodgenerator.update(dt);

   for (auto lesmaisons : maison){

       lesmaisons -> update(dt);
   }
   for(auto lesPher: pheromones) {

       lesPher->update(dt);

       if(lesPher->isNegligible()) {

           lesPher = nullptr;
           delete lesPher;

       }pheromones.erase(std::remove(pheromones.begin(), pheromones.end(), nullptr), pheromones.end());

}

}
void Environment:: drawOn(sf::RenderTarget& targetWindow) {
    for(auto food_dessin:nourritures){

        food_dessin->drawOn(targetWindow);
    }
    for(auto animal_dessin: faune){
        if(!animal_dessin->isDead()){

            animal_dessin->drawOn(targetWindow);
        }
    }
    for(auto pher_dessin: pheromones) {
        if(pher_ou_pas==true) {

           pher_dessin->drawOn(targetWindow);

             } else{

                pher_dessin = nullptr;
                delete pher_dessin;

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
   /* for(auto element_nourriture: nourritures){
        if(element_nourriture->getQuantity() ==0){
            delete  element_nourriture;
            element_nourriture = nullptr;
        }
    }*/
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

Quantities Environment:: getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position, Angle direction_rad, const Intervals &angles)
{
    Intervals ensemble_angles({-180, -100, -55, -25, -10,  0, 10, 25,  55, 100, 180 });

    Quantities Q(angles.size(), 0.0);

    for(auto les_pher: pheromones) {
        double smallest_dif=10000;
        unsigned int index(0);
        if(toricDistance(les_pher->getPosition(), position)<getAppConfig().ant_smell_max_distance){
            Vec2d gamma= position.toricVector(les_pher->getPosition());
            Angle beta= (gamma.angle()-direction_rad)/DEG_TO_RAD;

            while(beta<0){
                beta+=360;
            }
            while(beta>=360){
                beta=beta-360;
            }

            //Angle min=beta-angles[0];
            for(unsigned int i(0); i< angles.size(); ++i){
                Angle alpha=angles[i];
                /*while(alpha<0){
                    alpha+=360;
                }
                while (alpha>=360){
                    alpha-=360;
                }*/
                double difference(std::abs(beta-alpha));
                if(difference<smallest_dif){
                    smallest_dif=difference;
                    index=i;
                }

            }
            Q[index]=(les_pher->getQuantite());

        }
    }
    return Q;
}

bool Environment:: togglePheromoneDisplay()
{
  return pher_ou_pas = !pher_ou_pas;
}

Food* Environment::getClosestFoodForAnt(ToricPosition const& position){
    if (nourritures.size()>0){
    Food* min= nourritures[0];
    for(size_t i(0); i< nourritures.size(); ++i){
        if(toricDistance(nourritures[i]->getPosition(), position)<toricDistance(min->getPosition(), position)){
            min = nourritures[i];
        }}
    if(toricDistance(min->getPosition(), position) <= getAppConfig().ant_max_perception_distance){
            return min;
        }
    else {
        return nullptr;}
    }
}
Anthill* Environment ::getAnthillForAnt(ToricPosition const& position, Uid anthillId){
    Anthill* min = maison[1];
    if (maison.size()>0){
    for(size_t i(0); i< maison.size(); ++i){

        if(toricDistance(maison[i]->getPosition(), position)<= getAppConfig().ant_max_perception_distance and maison[i]->get_id() == anthillId){

            min = maison[i];
        }
        else {

            return nullptr;
        }

    }
    return min;
    } else {
        return nullptr;}
}
Animal* Environment :: getClosestAnimal(ToricPosition const& position){

    if(faune.size()>0){
        Animal* anim(faune[0]);
        for(unsigned int i(0); i<faune.size(); ++i){
            if(toricDistance(position, faune[i]->getPosition())< toricDistance(position, anim->getPosition())){
                anim=faune[i];
             }
         }
        if(toricDistance(anim->getPosition(), position) <= getAppConfig().animal_sight_distance){
            return anim ;

        } else {
            return nullptr;
            }
    } else {
        return nullptr;
        }

}

Environment:: ~Environment(){
    getAppEnv().reset();
}
