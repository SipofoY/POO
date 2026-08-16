#include "Environment.hpp"
#include<vector>
#include "Application.hpp"
#include"ToricPosition.hpp"
#include<SFML/Graphics.hpp>
#include"Animal.hpp"

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

void Environment:: update(sf::Time dt){
   for(auto lesAnimaux: faune){
       lesAnimaux->update(dt);
   }            //faire évoluer les animaux de la faune ici
   foodgenerator.update(dt);
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
    //a faire quand les animaux et les sources de nourriture deviendront plus concrets
}

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
}







