#include "AntWorker.hpp"
#include "Food.hpp"
#include "Anthill.hpp"
#include "Utility/Utility.hpp"
#include "Environment.hpp"


AntWorker::AntWorker(Vec2d position1, Uid fourmil)
    :Ant(position1, fourmil, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan)
{
    getAppEnv().increase_AW();
}

AntWorker::AntWorker(ToricPosition pos, Uid fourmil)
    :Ant(pos.toVec2d(), fourmil, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan)
{}

std::string AntWorker:: getTexture() const {
    return getAppConfig().ant_worker_texture;
}
void AntWorker::drawOn(sf::RenderTarget& target) const
{
    Ant::drawOn(target);
    if(isDebugOn()){
        auto const nourr_trans=buildText(to_nice_string(nourriture_transportee), getPosition().toVec2d() + Vec2d(0, 30), getAppFont(), 15, sf::Color::Black, 0 );
        target.draw(nourr_trans);
    }
}

void AntWorker:: demitour()
{
    double nouvdirection;
    nouvdirection = getDirection() + PI;
    setDirection(nouvdirection);
}


void AntWorker::update(sf::Time dt){
    Ant:: update(dt);

    Food* proche=getAppEnv().getClosestFoodForAnt(this->getPosition());
    Anthill* maison_proche=getAppEnv().getAnthillForAnt(this->getPosition(), this->get_id());

    if(nourriture_transportee==0 && proche!=nullptr and proche->getPoison() ==false and proche->getQuantity()!=0){
        nourriture_transportee+=proche->takeQuantity(getAppConfig().ant_max_food);
        demitour();
     }
    /*
    if(nourriture_transportee==0 && proche!=nullptr and proche->getPoison() ==true and proche->getQuantity()!=0){
        nourriture_transportee+=proche->takeQuantity(getAppConfig().ant_max_food);
        double point=getPointVie();
        point-=2;
        setpointdevie(point);
        demitour();
     }
*/

    if(maison_proche != nullptr and maison_proche->get_id()==get_id() and nourriture_transportee!=0 ){
        maison_proche->setstock(nourriture_transportee);
        nourriture_transportee=0;
        demitour();
     }
}

AntWorker:: ~AntWorker(){
    getAppEnv().decrease_AW();
}

