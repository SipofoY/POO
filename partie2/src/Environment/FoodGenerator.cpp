#include "FoodGenerator.hpp"
#include "Application.hpp"
#include"Environment.hpp"
#include"Random/Random.hpp"

FoodGenerator::FoodGenerator()
{
    compteur=sf::Time::Zero;
}

void FoodGenerator::update(sf::Time dt){


    compteur=compteur+dt;
    if(compteur>sf::seconds(getAppConfig().food_generator_delta)){
        double pos1 = normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4);
        double pos2=normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4);
        ToricPosition position(pos1,pos2);
        //Food food1(position,uniform(getAppConfig().food_min_qty, getAppConfig().food_max_qty));
        getAppEnv().addFood(new Food(position,uniform(getAppConfig().food_min_qty, getAppConfig().food_max_qty)));
        compteur=sf::Time::Zero;

    }
}
