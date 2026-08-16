#include "FoodGenerator.hpp"
#include "Application.hpp"
#include"Environment.hpp"
#include"Random/Random.hpp"
#include "Food.hpp"

FoodGenerator::FoodGenerator()
{
    compteur=sf::Time::Zero;
}

void FoodGenerator::update(sf::Time dt){

    compteur=compteur+dt;
    compteur1 = compteur1 + 1;

    if(compteur>sf::seconds(getAppConfig().food_generator_delta)){
        double pos1 = normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4);
        double pos2 = normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4);
        ToricPosition position(pos1,pos2);
        getAppEnv().addFood(new Food(position,uniform(getAppConfig().food_min_qty, getAppConfig().food_max_qty), getAppConfig().food_texture, false));
        compteur=sf::Time::Zero;

    }
    if ( compteur1 == 300){
        double posx1 = normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4);
        double posy1 = normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4);

        getAppEnv().addFood(new Food(Vec2d(posx1, posy1),uniform(getAppConfig().food_min_qty, getAppConfig().food_max_qty), getAppConfig().poison_texture, true));
        compteur1 = 0;

}
}
