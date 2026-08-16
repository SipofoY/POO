#include "Termite.hpp"
#include "Application.hpp"



Termite::Termite(ToricPosition pos)
    :Animal(pos, getAppConfig().termite_hp, getAppConfig().termite_lifespan)
{
    getAppEnv().increase_T();
}

int Termite:: getSpeed() const {
    return getAppConfig().termite_speed;
}

//void Termite:: move(sf::Time dt){
//    Animal::move(dt);
//}

std::string Termite:: getTexture() const{
    return getAppConfig().termite_texture;
}
void Termite:: drawOn(sf::RenderTarget& target) const {
    Animal::drawOn(target);

}

bool Termite::isEnemy(Animal const* animal) const {
     return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}

bool Termite::isEnemyDispatch(Termite const*) const {
    return false;
}

bool Termite::isEnemyDispatch(Ant const*) const {
    return true;
}

void Termite :: update(sf::Time dt){
    compteur = compteur + dt;
    Animal* proche=getAppEnv().getClosestEnemy(this);

    if(compteur.asSeconds()<=getAppConfig().termite_attack_delay){
        if(proche!=nullptr){
            Attack=true;
            double point=proche->getPointVie();
            point-=getAppConfig().termite_strength;
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


Termite::~Termite(){
    getAppEnv().decrease_T();
}







