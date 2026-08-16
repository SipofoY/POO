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

void Environment:: addAnthill(Anthill* anthill){
    if(anthill!=nullptr){
        maison.push_back(anthill);
    }
}

void Environment:: update(sf::Time dt)
{
    for(auto& lesAnimaux: faune) {
        if(!lesAnimaux->isDead()){
            lesAnimaux->update(dt);
        }
        else {
           delete lesAnimaux;
           lesAnimaux=nullptr;
        }

    } faune.erase(std::remove(faune.begin(), faune.end(), nullptr), faune.end());

    foodgenerator.update(dt);

    for(auto& lesPher: pheromones) {
            lesPher->update(dt);
            if(lesPher->isNegligible()) {

                lesPher=nullptr;
                delete  lesPher;
            }

    } pheromones.erase(std::remove(pheromones.begin(), pheromones.end(), nullptr), pheromones.end());


    for (auto& lesmaisons : maison) {
        lesmaisons -> update(dt);
    }
}

void Environment:: drawOn(sf::RenderTarget& targetWindow)
{
    for(auto& food_dessin:nourritures) {
        food_dessin->drawOn(targetWindow);
    }

     for(auto& animal_dessin: faune) {
        if(!animal_dessin->isDead()) {
            animal_dessin->drawOn(targetWindow);
        }
    }

    for(auto& pher_dessin: pheromones) {
        if(pher_ou_pas) {                
            pher_dessin->drawOn(targetWindow);

        }
    } pheromones.erase(std::remove(pheromones.begin(), pheromones.end(), nullptr), pheromones.end());

    for (auto& maison_dessin: maison) {
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
  return pher_ou_pas= !pher_ou_pas;
}

Quantities Environment:: getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position, Angle direction_rad, const Intervals &angles)
{
    Quantities Q(angles.size(), 0.0);

    for(auto& les_pher: pheromones) {
        double smallest_dif=100000;
        unsigned int index(0);
        if(toricDistance(les_pher->getPosition(), position)<=getAppConfig().ant_smell_max_distance){
            Vec2d gamma = position.toricVector(les_pher->getPosition());
            Angle beta = (gamma.angle()-direction_rad)/DEG_TO_RAD;

            while(beta<0){
                beta+=360;
            }
            while(beta>=360){
                beta=beta-360;
            }

            for(unsigned int i(0); i< angles.size(); ++i){
                double alpha(angles[i]);
                while (alpha<0){
                    alpha+=360;
                }
                while(alpha>=360){
                    alpha-=360;
                }
                double difference(std::abs(beta-angles[i]));

                if(difference<smallest_dif){
                    smallest_dif=difference;
                    index=i;
                }
            }
            Q[index]+=les_pher->getQuantite();
           // std:: cerr <<Q[index]<<std::endl;  //print 0
        }
    }
    return Q;
}

Environment:: ~Environment(){
    getAppEnv().reset();
}


Food* Environment::getClosestFoodForAnt(ToricPosition const& position){

    if(nourritures.size()>0){
        Food* closest_food(nourritures[0]);
        for(unsigned int i(0); i<nourritures.size(); ++i){
            if(toricDistance(position, nourritures[i]->getPosition())< toricDistance(position, closest_food->getPosition())){
                closest_food=nourritures[i];
            }
        }
        if(toricDistance(closest_food->getPosition(), position) <= getAppConfig().ant_max_perception_distance){
            return closest_food;

        }
        else {
            return nullptr;
        }
    }
    else {
        return nullptr;
    }
}



Anthill* Environment ::getAnthillForAnt(ToricPosition const& position, Uid anthillId){

    if(maison.size()>0){
        Anthill* home(maison[0]);
        for(unsigned int i(0); i<maison.size(); ++i){
            if (maison[i]->get_id() == anthillId /*and toricDistance(position, maison[i]->getPosition())<toricDistance(position, home->getPosition())*/){
                home=maison[i];
            }
        }
        if(toricDistance(position, home->getPosition())<=getAppConfig().ant_max_perception_distance){
            return home;
        }
        else {
            return nullptr;
        }
    }
    else {
        return nullptr;
    }
}


Animal* Environment :: getClosestEnemy(Animal* predator){

    Animal* anim(nullptr);
    if(faune.size()>0){
        for(unsigned int i(0); i<faune.size(); ++i){
            if(faune[i]!=nullptr and toricDistance(predator->getPosition(), faune[i]->getPosition())<=getAppConfig().animal_sight_distance and faune[i]->isEnemy(predator)){
                anim=faune[i];    
             }
        }
    }
    return anim;
}



void Environment:: decrease_AW(){
    --antworker_compteur;
}

void Environment:: increase_AW(){
    ++antworker_compteur;
}

void Environment:: decrease_AS(){
    --antsoldier_compteur;
}

void Environment:: increase_AS(){
    ++antsoldier_compteur;
}

void Environment:: decrease_T(){
    --termite_compteur;
}

void Environment:: increase_T(){
    ++termite_compteur;
}



double Environment:: getTemperature(){
    return Temperature;
}

//Quantity Environment :: getTotalFood(){
//    return foodTotal;
//}


std::unordered_map<std::string, double> Environment::fetchData(const std::string & title)
{
    std::unordered_map<std::string, double> new_data;
    if(title==s::GENERAL){
        new_data.insert({{"worker ants", getAppEnv().antworker_compteur}, {"soldier ants", getAppEnv().antsoldier_compteur},
                         {"termites", getAppEnv().termite_compteur}, {"temperature", getAppEnv().getTemperature()}});
    }

    if(title==s::FOOD){
        new_data.insert({{"food", Food::getTotalFood()}});
    }

    if(title==s::ANTHILLS){
        for(unsigned int i(0); i<maison.size(); ++i){
             new_data.insert({{getAppEnv().getAnthillsIds()[i], maison[i]->getStock()}});
        }        
    }
    return new_data;
}


std::vector<std::string> Environment::getAnthillsIds() const
{
    std::vector<std::string> anthill_names;
    if(maison.size()>0){
        for(auto& anthill: maison){
            anthill_names.push_back("anthill #" + to_nice_string(anthill->get_id()));
        }
    }
    return anthill_names;
}





