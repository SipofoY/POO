#include "AntWorker.hpp"
#include"Utility/Utility.hpp"
#include"Food.hpp"
#include "Anthill.hpp"

AntWorker::AntWorker(Vec2d position1, Uid fourmil)
     :Ant(position1,fourmil,getAppConfig().ant_worker_lifespan,getAppConfig().ant_worker_hp)
{}
AntWorker::AntWorker(ToricPosition position1, Uid fourmil)
    :Ant(position1.toVec2d(),fourmil,getAppConfig().ant_worker_lifespan,getAppConfig().ant_worker_hp)
{}


void AntWorker::drawOn(sf::RenderTarget& target) const{
    drawnAnt(target,getAppConfig().ant_worker_texture);
    auto const nourr_trans = buildText(to_nice_string(nourriture_transportee), getPosition().toVec2d() + Vec2d(0,15), getAppFont(), 15, sf::Color::Blue);
    target.draw(nourr_trans);
    auto const id = buildText(to_nice_string(get_id()), getPosition().toVec2d() + Vec2d(0,-30), getAppFont(), 15, sf::Color::Cyan);
    target.draw(id);

    }

void AntWorker::update(sf::Time dt) {
    if(Attack == true and Idle == false){

        move(sf::Time::Zero);}
    updatAnt(dt);
    Food* proche = getAppEnv().getClosestFoodForAnt(this->getPosition());
    if(nourriture_transportee < getAppConfig().ant_max_food && proche!= nullptr and proche->getQuantity() !=0){
        //std::cout<<"test"<< std::endl;
        proche -> takeQuantity(getAppConfig().ant_max_food);
        nourriture_transportee += getAppConfig().ant_max_food;
        demitour();
    }
    Anthill* maison_proche = getAppEnv().getAnthillForAnt(this->getPosition(), this->get_id());
        if (maison_proche!= nullptr and maison_proche ->get_id() == get_id() and nourriture_transportee !=0){
            maison_proche ->setstock(getAppConfig().ant_max_food);
            nourriture_transportee =0;
            demitour();

    }
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
    }




void AntWorker:: demitour(){

    double nouvdirection;
    nouvdirection = getDirection() + PI;
    setDirection(nouvdirection);
}

