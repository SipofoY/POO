#include "AntWorker.hpp"
#include "Food.hpp"
#include "Anthill.hpp"
#include "Utility/Utility.hpp"
#include "Environment.hpp"


AntWorker::AntWorker(Vec2d position1, Uid fourmil)
    :Ant(position1, fourmil, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan)
{}

AntWorker::AntWorker(ToricPosition pos, Uid fourmil)
    :Ant(pos.toVec2d(), fourmil, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan)
{}


void AntWorker::drawOn(sf::RenderTarget& target) const
{
    drawnAnt(target,getAppConfig().ant_worker_texture);
    auto const nourr_trans=buildText(to_nice_string(nourriture_transportee), getPosition().toVec2d() + Vec2d(0, 10), getAppFont(), 15, sf::Color::Black, 0 );
    target.draw(nourr_trans);
}

void AntWorker:: demitour()
{
    double nouvdirection;
    nouvdirection = getDirection() + PI;
    setDirection(nouvdirection);
}

/*void AntWorker:: setmaxfood(double quantite){

    if ((quantite+maxfood) < getAppConfig().ant_max_food){

        maxfood = maxfood + quantite;
    } else {
        maxfood = getAppConfig().ant_max_food;
    }

}
void AntWorker:: resetfood(){
    maxfood = 0;
}*/

void AntWorker::update(sf::Time dt){
    updateAnt(dt);

    Food* proche=getAppEnv().getClosestFoodForAnt(this->getPosition());
    Anthill* maison_proche=getAppEnv().getAnthillForAnt(this->getPosition(), this->get_id());
    Quantity n(0.0);
    if(nourriture_transportee==0 && proche!=nullptr and proche->getQuantity()!=0){
        if(proche->getQuantity()<getAppConfig().ant_max_food){
            n=proche->getQuantity();
        } else{
            n=getAppConfig().ant_max_food;
            }
        proche->takeQuantity(n);
        nourriture_transportee+=n;
        demitour();
     }

    if(maison_proche != nullptr and maison_proche->get_id()==get_id() and nourriture_transportee!=0 ){
        maison_proche->setstock(getAppConfig().ant_max_food);
        nourriture_transportee=0;
        demitour();
     }

    if(Idle){
        Ant::move(dt);
    }


}


