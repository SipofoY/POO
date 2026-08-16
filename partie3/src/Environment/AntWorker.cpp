#include "AntWorker.hpp"

AntWorker::AntWorker(Vec2d position1, Uid fourmil)
     :Ant(position1,fourmil,getAppConfig().ant_worker_lifespan,getAppConfig().ant_worker_hp)
{}
AntWorker::AntWorker(ToricPosition position1, Uid fourmil)
    :Ant(position1.toVec2d(),fourmil,getAppConfig().ant_worker_lifespan,getAppConfig().ant_worker_hp)
{}


void AntWorker::drawOn(sf::RenderTarget& target) const{
    drawnAnt(target,getAppConfig().ant_worker_texture);
}
void AntWorker::update(sf::Time dt) {
    updatAnt(dt);
 }
void AntWorker:: demitour(){

    double nouvdirection;
    nouvdirection = getDirection() + PI;
    setDirection(nouvdirection);
}
void AntWorker:: setmaxfood(double food){

    maxfood = maxfood + food;
}
void AntWorker:: resetfood(){
    maxfood = 0;
}
