#include "AntSoldier.hpp"

AntSoldier::AntSoldier(Vec2d position1, Uid fourmil)
    :Ant(position1, fourmil,getAppConfig().ant_soldier_hp,getAppConfig().ant_soldier_lifespan )//que mettre comme arguments
{}
/*AntSoldier::AntSoldier(ToricPosition position1, Uid fourmil)
    :Ant(position1.toVec2d(), fourmil,getAppConfig().ant_soldier_hp,getAppConfig().ant_soldier_lifespan)
{}
*/
void AntSoldier::drawOn(sf::RenderTarget& target) const{
    drawnAnt(target,getAppConfig().ant_soldier_texture);

}
void AntSoldier::update(sf::Time dt){
    updatAnt(dt);

    if (Attack == false and Idle == true){
    if ((toricDistance(getAppEnv().getClosestAnimal(getPosition())->getPosition(),getPosition()) <= getAppConfig().animal_sight_distance) and (isEnemy(getAppEnv().getClosestAnimal(getPosition())) == false)){
     Attack = true;
     Idle = false;
    }
    if (Attack == true and Idle == false){
    while(compteur<=getAppConfig().ant_attack_delay){
        if (compteur == getAppConfig().ant_attack_delay){
        Attack = false;
        Idle = true;
        }
        compteur = compteur + dt.asSeconds();
        getAppEnv().getClosestAnimal(getPosition())-> setpointdevie(getAppConfig().ant_soldier_strength);
        move(sf::Time::Zero);
        }
       // std::cout<<"test"<<std::endl;
    }
    }
    }



