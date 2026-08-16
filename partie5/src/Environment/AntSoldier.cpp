#include "AntSoldier.hpp"


AntSoldier::AntSoldier(Vec2d position1, Uid fourmil)    
    :Ant(position1, fourmil, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan)
{
   getAppEnv().increase_AS();
}

std::string AntSoldier::getTexture() const{
    return getAppConfig().ant_soldier_texture;
}

void AntSoldier::drawOn(sf::RenderTarget& target) const
{
    Ant::drawOn(target);
}


void AntSoldier::update(sf::Time dt) {
    compteur = compteur + dt;
    Animal* proche=getAppEnv().getClosestEnemy(this);

    if(compteur.asSeconds()<=getAppConfig().ant_attack_delay){
        if(proche!=nullptr){
            Attack=true;
            double point=proche->getPointVie();
            point-=getAppConfig().ant_soldier_strength;
            proche->setpointdevie(point);
        }

        if (!Attack){
            Animal::update(dt);
        }
    }
    else {
        Attack=false;
        compteur=sf::Time::Zero;
    }
}


AntSoldier::~AntSoldier(){
    getAppEnv().decrease_AS();
}
