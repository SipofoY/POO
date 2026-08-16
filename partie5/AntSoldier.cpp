#include "AntSoldier.hpp"


AntSoldier::AntSoldier(Vec2d position1, Uid fourmil)    
    :Ant(position1, fourmil, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan)
{}

void AntSoldier::drawOn(sf::RenderTarget& target) const
{
    drawnAnt(target,getAppConfig().ant_soldier_texture);
}

void AntSoldier::update(sf::Time dt){
    updateAnt(dt);
    Animal* proche = getAppEnv().getClosestEnemy(this);
    double point=proche->getPointVie();

    //std::cout<<proche->getPosition()<<std::endl;
    if (Idle){
       Animal::move(dt);
       if(proche!=nullptr){
            Attack=true;
            std::cout<<"test"<<std::endl;
        }
    }

    if (Attack){

        while(compteur.asSeconds()<=getAppConfig().ant_attack_delay){
                compteur = compteur + dt;
                point-=getAppConfig().ant_soldier_strength;
                proche->setpointdevie(point);
                //std::cout<<pointvie<<std::endl;
                //move(sf::Time::Zero);
        }

        if (compteur.asSeconds() >= getAppConfig().ant_attack_delay){
            Attack = false;
            compteur=sf::Time::Zero;

        }

    }

}



